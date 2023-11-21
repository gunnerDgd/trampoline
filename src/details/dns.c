#include "dns.h"
#include "endian.h"

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
        (__dns* par_dns, u32_t par_count, va_list par)                             {
            alloc* par_alloc = (par_count == 0) ? get_alloc() : va_arg(par, alloc*);
            if (!par_alloc)
                return false_t;

            if(!make_at(par_dns->req       , list_t) from(1, par_alloc)) goto __dns_init_failed;
            if(!make_at(par_dns->res       , list_t) from(1, par_alloc)) goto __dns_init_failed;
            if(!make_at(par_dns->auth      , list_t) from(1, par_alloc)) goto __dns_init_failed;
            if(!make_at(par_dns->additional, list_t) from(1, par_alloc)) goto __dns_init_failed;

            par_dns->ptr     = ptr_null();
            par_dns->ptr_off = ptr_null();

            return true_t;
    __dns_init_failed:
            del(&par_dns->req)       ;
            del(&par_dns->res)       ;
            del(&par_dns->auth)      ;
            del(&par_dns->additional);
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
}

u64_t
    __dns_size()            {
        return sizeof(__dns);
}