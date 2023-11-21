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
        (__dns_builder* par_builder, u32_t par_count, va_list par)                   {
            par_builder->alloc = (par_count == 1) ? va_arg(par, alloc*) : get_alloc();
            if (!par_builder->alloc)
                return false_t;

            if(!(par_builder->mem = make (box_t)        from (2, 512, par_builder->alloc))) return false_t;
            if(!(par_builder->dns = make (&__dns_trait) from (1, par_builder->mem))) {
                del(par_builder->mem);
                return false_t;
            }

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
            del(par->mem);
}

u64_t  
    __dns_builder_size()            {
        return sizeof(__dns_builder);
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
            if (!null(par->dns->ptr_off)) {
                del(&par->dns->dns_head);
                return false_t;
            }

            return true_t;
}

bool_t 
    __dns_build_req
        (__dns_builder* par, __dns_name* par_req, u16_t par_type, u16_t par_cls) {
            __dns_req* req = make(&__dns_req_trait) from (
                4       ,
                par->dns,
                par_req ,
                par_type,
                par_cls
            );

            if (!req)       return false_t;
            if (!null(par->dns->ptr_off)) {
                del(req)      ;
                return false_t;
            }
            
            list_push_back(&par->dns->req, req); ++par->req;
            del(req)     ;
            return true_t;
}

bool_t 
    __dns_build_res
        (__dns_builder* par, __dns_name* par_req, u16_t par_type, u16_t par_cls, u16_t par_ttl, __dns_name* par_res) {
            __dns_res* res = make(&__dns_res_trait) from (
                6       ,
                par->dns,
                par_req ,
                par_type,
                par_cls ,
                par_ttl ,
                par_res
            );

            if (!res)       return false_t;
            if (!null(par->dns->ptr_off)) {
                del(res)      ;
                return false_t;
            }
            
            list_push_back(&par->dns->res, res); ++par->res;
            del           (res);
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