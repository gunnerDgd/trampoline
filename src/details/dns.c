#include "dns.h"

obj_trait __dns_trait                  = {
    .init          = &__dns_init         ,
    .init_as_clone = &__dns_init_as_clone,
    .init_as_ref   =                    0,
    .deinit        = &__dns_deinit       ,
    .name          =                    0,
    .size          = &__dns_size
};

bool_t 
    __dns_init
        (__dns* par_dns, u32_t par_count, va_list par) {
            par_dns->mem = ref(va_arg(par, box*));
            if (!par_dns->mem)
                return false_t;

            if(!make_at(par_dns->req       , list_t) from(0)) goto __dns_init_failed;
            if(!make_at(par_dns->res       , list_t) from(0)) goto __dns_init_failed;
            if(!make_at(par_dns->auth      , list_t) from(0)) goto __dns_init_failed;
            if(!make_at(par_dns->additional, list_t) from(0)) goto __dns_init_failed;

            if (par_count == 1)                            {
                par_dns->ptr     = box_ptr(par_dns->mem, 0);
                par_dns->ptr_off = par_dns->ptr            ;

                return true_t;
            }

            par_dns->ptr     = box_ptr(par_dns->mem, va_arg(par, u64_t));
            par_dns->ptr_off = par_dns->ptr                             ;
            
            if (!make_at(par_dns->dns_head, &__dns_head_trait) from(1, par_dns))
                goto __dns_init_failed;

            if (!__dns_req_parse(par_dns)) goto __dns_init_failed;
            if (!__dns_res_parse(par_dns)) goto __dns_init_failed;

            return true_t;
    __dns_init_failed:
            del(&par_dns->req)       ;
            del(&par_dns->res)       ;
            del(&par_dns->auth)      ;
            del(&par_dns->additional);
            
            del(par_dns->mem);
            return false_t;
}

bool_t 
    __dns_init_as_clone
        (__dns* par, __dns* par_clone) {
            return false_t;
}

void   
    __dns_deinit
        (__dns* par)             {
            del(&par->req)       ;
            del(&par->res)       ;
            del(&par->auth)      ;
            del(&par->additional);
            del(par->mem)        ;
}

u64_t
    __dns_size()            {
        return sizeof(__dns);
}

bool_t 
    __dns_req_parse
        (__dns* par)                                                 {
            u16_t   req_count = __dns_head_req(&par->dns_head)       ;
            for ( ; req_count > 0 ; --req_count)                     {
                __dns_req* req = make(&__dns_req_trait) from (1, par);

                if (!req)         {
                    del(req)      ;
                    return false_t;
                }

                if (null(par->ptr_off)) {
                    del(req)      ;
                    return false_t;
                }

                list_push_back(&par->req, req);
                del(req);
            }

            return true_t;
}

bool_t 
    __dns_res_parse
        (__dns* par)                                                 {
            u16_t   res_count = __dns_head_res(&par->dns_head)       ;
            for ( ; res_count > 0 ; --res_count)                     {
                __dns_res* res = make(&__dns_res_trait) from (1, par);

                if (!res)         {
                    del(res)      ;
                    return false_t;
                }

                if (null(par->ptr_off)) {
                    del(res)      ;
                    return false_t;
                }

                list_push_back(&par->res, res);
                del(res);
            }

            return true_t;
}

u16_t  __dns_id       (__dns* par) { return __dns_head_id    (&par->dns_head); }
u16_t  __dns_opcode   (__dns* par) { return __dns_head_opcode(&par->dns_head); }
u64_t  __dns_len      (__dns* par) { return ptr_dist (par->ptr, par->ptr_off); }
it     __dns_req_begin(__dns* par) { return list_begin       (&par->req)     ; }
it     __dns_req_end  (__dns* par) { return list_end         (&par->req)     ; }
u16_t  __dns_req_count(__dns* par) { return __dns_head_req   (&par->dns_head); }

it     __dns_res_begin(__dns* par) { return list_begin       (&par->res)     ; }
it     __dns_res_end  (__dns* par) { return list_end         (&par->res)     ; }
u16_t  __dns_res_count(__dns* par) { return __dns_head_res   (&par->dns_head); }