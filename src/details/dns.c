#include "dns.h"
#include "endian.h"

#include <stdio.h>

obj_trait dns_t                      = {
    .init          = &dns_init         ,
    .init_as_clone = &dns_init_as_clone,
    .init_as_ref   =                  0,
    .deinit        = &dns_deinit       ,
    .name          =                  0,
    .size          = &dns_size
};

bool_t 
    dns_init
        (dns* par_dns, u32_t par_count, va_list par)                               {
            alloc* par_alloc = (par_count == 0) ? get_alloc() : va_arg(par, alloc*);
            if (!par_alloc)
                return false_t;

            if(!make_at(par_dns->req       , list_t) from(1, par_alloc)) goto dns_init_failed;
            if(!make_at(par_dns->res       , list_t) from(1, par_alloc)) goto dns_init_failed;
            if(!make_at(par_dns->auth      , list_t) from(1, par_alloc)) goto dns_init_failed;
            if(!make_at(par_dns->additional, list_t) from(1, par_alloc)) goto dns_init_failed;

            par_dns->ptr     = ptr_null();
            par_dns->ptr_off = ptr_null();

            return true_t;
    dns_init_failed:
            del(&par_dns->req)       ;
            del(&par_dns->res)       ;
            del(&par_dns->auth)      ;
            del(&par_dns->additional);
            return false_t;
}

bool_t 
    dns_init_as_clone
        (dns* par, dns* par_clone) {
            return false_t;
}

void   
    dns_deinit
        (dns* par)               {
            del(&par->req)       ;
            del(&par->res)       ;
            del(&par->auth)      ;
            del(&par->additional);
            del(&par->dns_head)  ;

            printf("DNS DELETEED\n");
}

u64_t
    dns_size()            {
        return sizeof(dns);
}