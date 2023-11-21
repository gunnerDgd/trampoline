#include "parse.h"
#include "endian.h"

obj_trait __dns_parser_trait                  = {
    .init          = &__dns_parser_init         ,
    .init_as_clone = &__dns_parser_init_as_clone,
    .init_as_ref   =                           0,
    .deinit        = &__dns_parser_deinit       ,
    .name          =                           0,
    .size          = &__dns_parser_size
};

bool_t 
    __dns_parser_init
        (__dns_parser* par_parser, u32_t par_count, va_list par) {
            par_parser->dns = 0;

            par_parser->req_type    = 0;
            par_parser->req_cls     = 0;

            par_parser->res_type    = 0;
            par_parser->res_cls     = 0;
            par_parser->res_req     = 0;

            return true_t;
}

bool_t 
    __dns_parser_init_as_clone
        (__dns_parser* par, __dns_parser* par_clone) {
            return false_t;
}

void
    __dns_parser_deinit
        (__dns_parser* par)                    {
            if (par->dns)     del(par->dns)    ;
            if (par->res_req) del(par->res_req);
}

u64_t
    __dns_parser_size()            {
        return sizeof(__dns_parser);
}

bool_t 
    __dns_do_parse_head
        (__dns_parser* par) {
            if(!par->dns) 
                return false_t;

            return make_at(par->dns->dns_head, &__dns_head_trait) from(1, par->dns);
}

bool_t 
    __dns_do_parse_req
        (__dns_parser* par)                                        {
            u16_t  req_count = be16(par->dns->dns_head.form->req);
            while (req_count--)                                          {
                __dns_req* req = make(&__dns_req_trait) from(1, par->dns);
                if (!req)
                    return false_t;

                u16_t type, cls;
                if (null(ptr_rd16(req->form.type, &type))) return false_t;
                if (null(ptr_rd16(req->form.cls , &cls)))  return false_t;

                if (par->req_type && be16(type) != par->req_type) { del(req); continue; }
                if (par->req_cls  && be16(cls)  != par->req_cls)  { del(req); continue; }

                list_push_back(&par->dns->req, req);
                del                           (req);
            }

            return true_t;
}

bool_t 
    __dns_do_parse_res
        (__dns_parser* par)                                      {
            u16_t  res_count = be16(par->dns->dns_head.form->res);
            while (res_count--)                                           {
                __dns_res *res = make(&__dns_res_trait) from (1, par->dns);
                if (!res)
                    return false_t;

                u16_t       type, cls;
                __dns_name* req = make(&__dns_name_trait) from(0);

                if (!req)                                         { del(res); return false_t; }
                if (null(ptr_rd16(res->form.type, &type)))        { del(res); return false_t; }
                if (null(ptr_rd16(res->form.cls , &cls )))        { del(res); return false_t; }

                if (par->res_type && be16(type) != par->res_type) { del(res); continue; }
                if (par->res_cls  && be16(cls)  != par->res_cls)  { del(res); continue; }
                if (par->res_req)                                                 {
                    if (!__dns_name_from_ptr(req, res->form.name, par->dns->ptr)) {
                        del      (res); 
                        return false_t;
                    }

                    if (!str_eq(req, par->res_req)) { 
                        del(res); 
                        continue; 
                    }
                }

                list_push_back(&par->dns->res, res);
                del                           (res);
            }

            return true_t;
}


void
    __dns_parse_req
        (__dns_parser* par, u16_t par_type, u16_t par_cls) {
            par->req_type = par_type;
            par->req_cls  = par_cls ;
}

void 
    __dns_parse_res
        (__dns_parser* par, u16_t par_type, u16_t par_cls, __dns_name* par_req) {
            par->res_type = par_type;
            par->res_cls  = par_cls ;
            par->res_req  = par_req ;
}

__dns* 
    __dns_parse
        (__dns_parser* par)                              {
            if (!par->dns)                 return false_t;
            if (!__dns_do_parse_head(par)) return false_t;
            if (!__dns_do_parse_req (par)) return false_t;
            if (!__dns_do_parse_res (par)) return false_t;

            return ref(par->dns);
}