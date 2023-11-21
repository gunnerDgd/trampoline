#include "dns.h"
#include "details/dns.h"

#include "endian.h"

obj_trait* dns_t = &__dns_trait;

u64_t 
    dns_len
        (obj* par)                              {
            if (!par)                   return 0;
            if (trait_of(par) != dns_t) return 0;

            return ptr_dist(((__dns*)par)->ptr, ((__dns*)par)->ptr_off);
}

obj* 
    dns_head
        (obj* par)                              {
            if (!par)                   return 0;
            if (trait_of(par) != dns_t) return 0;

            return &((__dns*)par)->dns_head;
}

it    
    dns_req_begin
        (obj* par)                                   {
            if (!par)                   return npos();
            if (trait_of(par) != dns_t) return npos();

            return list_begin(&((__dns*)par)->req);
}

it    
    dns_req_end
        (obj* par)                                   {
            if (!par)                   return npos();
            if (trait_of(par) != dns_t) return npos();

            return list_end(&((__dns*)par)->req);
}

u16_t 
    dns_req_count
        (obj* par)                                    {
            if (!par)                   return false_t;
            if (trait_of(par) != dns_t) return false_t;

            return be16(((__dns*)par)->dns_head.form->req);
}

it    
    dns_res_begin
        (obj* par)                                   {
            if (!par)                   return npos();
            if (trait_of(par) != dns_t) return npos();

            return list_begin(&((__dns*)par)->res);
}

it    
    dns_res_end
        (obj* par)                                   {
            if (!par)                   return npos();
            if (trait_of(par) != dns_t) return npos();

            return list_end(&((__dns*)par)->res);
}

u16_t 
    dns_res_count
        (obj* par)                                    {
            if (!par)                   return false_t;
            if (trait_of(par) != dns_t) return false_t;

            return be16(((__dns*)par)->dns_head.form->res);
}