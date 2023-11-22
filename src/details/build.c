#include "build.h"
#include "endian.h"

obj_trait __dns_builder_trait                  = {
    .init          = &__dns_builder_init         ,
    .init_as_clone = &__dns_builder_init_as_clone,
    .init_as_ref   =                            0,
    .deinit        = &__dns_builder_deinit       ,
    .name          =                            0,
    .size          = &__dns_builder_size
};

bool_t 
    __dns_builder_init
        (__dns_builder* par_builder, u32_t par_count, va_list par)                 {
            alloc* par_alloc = (par_count == 0) ? get_alloc() : va_arg(par, alloc*);
            par_builder->dns = make(&__dns_trait) from (1, par_alloc);
            if (!par_builder->dns)
                return false_t;

            par_builder->req        = 0;
            par_builder->res        = 0;
            par_builder->auth       = 0;
            par_builder->additional = 0;

            return true_t;
}

bool_t 
    __dns_builder_init_as_clone
        (__dns_builder* par, __dns_builder* par_clone) {
            return false_t;
}

void   
    __dns_builder_deinit
        (__dns_builder* par) {
            del(par->dns);
}

u64_t  
    __dns_builder_size()            {
        return sizeof(__dns_builder);
}

bool_t 
    __dns_build_from
        (__dns_builder* par, ptr par_ptr)                            {
            if (null(par_ptr))                         return false_t;
            if (trait_of(par) != &__dns_builder_trait) return false_t;
            if (!par)                                  return false_t;
            
            
            par->dns->ptr     = par_ptr;
            par->dns->ptr_off = par_ptr;

            return true_t;
}

bool_t 
    __dns_build_from_existing
        (__dns_builder* par, __dns* par_dns)                         {
            if (trait_of(par) != &__dns_builder_trait) return false_t;
            if (!par)                                  return false_t;
            if (trait_of(par_dns) != &__dns_trait)     return false_t;
            if (!par_dns)                              return false_t;

            del(par->dns);
            par->dns        = par_dns;
            par->req        = be16(par_dns->dns_head.form->req)       ;
            par->res        = be16(par_dns->dns_head.form->res)       ;
            par->auth       = be16(par_dns->dns_head.form->auth)      ;
            par->additional = be16(par_dns->dns_head.form->additional);

            return true_t;
}

bool_t 
    __dns_build_head
        (__dns_builder* par, u16_t par_id, u16_t par_opcode)                 {
            bool_t ret = make_at(par->dns->dns_head, &__dns_head_trait) from (
                3         ,
                par->dns  ,
                par_id    ,
                par_opcode
            );          

            if (!ret)       return false_t;
            if (null(par->dns->ptr_off))  {
                del(&par->dns->dns_head);
                return false_t;
            }

            return true_t;
}

bool_t 
    __dns_build_req
        (__dns_builder* par, __dns_name* par_req, u16_t par_type, u16_t par_cls)    {
            if(!par     || trait_of(par)     != &__dns_builder_trait) return false_t;
            if(!par_req || trait_of(par_req) != &__dns_name_trait)    return false_t;

            if(par->res)        return false_t;
            if(par->auth)       return false_t;
            if(par->additional) return false_t;

            __dns_req* req = make(&__dns_req_trait) from (
                4       ,
                par->dns,
                par_req ,
                par_type,
                par_cls
            );

            if (!req)       return false_t;
            if (null(par->dns->ptr_off))  {
                del(req)      ;
                return false_t;
            }
            
            list_push_back(&par->dns->req, req); ++par->req;
            del(req)     ;
            return true_t;
}

bool_t 
    __dns_build_res_a
        (__dns_builder* par, __dns_name* par_name, u16_t par_cls, u32_t par_ttl, u32_t par_v4) {
            if(!par      || trait_of(par)      != &__dns_builder_trait) return false_t;
            if(!par_name || trait_of(par_name) != &__dns_name_trait)    return false_t;

            if(!par->req)        return false_t;
            if (par->auth)       return false_t;
            if (par->additional) return false_t;

            __dns_res* res = make(&__dns_res_trait) from (
                7       ,
                par->dns,
                par_name,
                1       ,
                par_cls ,
                par_ttl ,
                4       ,
                &par_v4
            );

            if (!res)            return false_t;
            list_push_back(&par->dns->res, res);

            del     (res);
            return true_t;
}

bool_t 
    __dns_build_res_cname
        (__dns_builder* par, __dns_req* par_req, u16_t par_cls, u32_t par_ttl, __dns_name* par_cname) {
            if(!par     || trait_of(par)     != &__dns_builder_trait) return false_t;
            if(!par_req || trait_of(par_req) != &__dns_req_trait)     return false_t;

            if(!par->req)        return false_t;
            if (par->auth)       return false_t;
            if (par->additional) return false_t;

            __dns_res* res = make(&__dns_res_trait) from (
                7       ,
                par->dns,
                par_req ,
                5       ,
                par_cls ,
                par_ttl ,
                0       ,
                0
            );

            if (!res) return false_t;
            ptr  ret = __dns_name_to_ptr(par_cname, res->form.data, par->dns->ptr);

            if (null(ret))    {
                del      (res);
                return false_t;
            }
            
            list_push_back(&par->dns->res, res);
            par->dns->ptr_off = ret;
            
            ptr_wr16(res->form.data_len, be16(ptr_dist(par->dns->ptr_off, res->form.data)));
            return true_t;
}

__dns* 
    __dns_build
        (__dns_builder* par)                                           {
            par->dns->dns_head.form->req        = be16(par->req)       ;
            par->dns->dns_head.form->res        = be16(par->res)       ;
            par->dns->dns_head.form->auth       = be16(par->auth)      ;
            par->dns->dns_head.form->additional = be16(par->additional);

            return ref(par->dns);
}