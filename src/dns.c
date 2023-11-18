#include "dns.h"
#include "details/dns.h"

obj_trait* dns_t = &__dns_trait;

u16_t 
    dns_id
        (dns* par)                                    {
            if (!par)                   return false_t;
            if (trait_of(par) != dns_t) return false_t;

            return __dns_id(par);
}

box*
    dns_mem
        (dns* par)                                    {
            if (!par)                   return false_t;
            if (trait_of(par) != dns_t) return false_t;

            return ((__dns*)par)->mem;
}

u16_t 
    dns_opcode
        (dns* par)                                    {
            if (!par)                   return false_t;
            if (trait_of(par) != dns_t) return false_t;

            return __dns_opcode(par);
}

u64_t 
    dns_len
        (dns* par)                                    {
            if (!par)                   return false_t;
            if (trait_of(par) != dns_t) return false_t;

            return __dns_len(par);
}

it    
    dns_req_begin
        (dns* par)                                   {
            if (!par)                   return npos();
            if (trait_of(par) != dns_t) return npos();

            return __dns_req_begin(par);
}

it    
    dns_req_end
        (dns* par)                                   {
            if (!par)                   return npos();
            if (trait_of(par) != dns_t) return npos();

            return __dns_req_end(par);
}

u16_t 
    dns_req_count
        (dns* par)                                    {
            if (!par)                   return false_t;
            if (trait_of(par) != dns_t) return false_t;

            return __dns_req_count(par);
}

it    
    dns_res_begin
        (dns* par)                                   {
            if (!par)                   return npos();
            if (trait_of(par) != dns_t) return npos();

            return __dns_res_begin(par);
}

it    
    dns_res_end
        (dns* par)                                   {
            if (!par)                   return npos();
            if (trait_of(par) != dns_t) return npos();

            return __dns_res_end(par);
}

u16_t 
    dns_res_count
        (dns* par)                                    {
            if (!par)                   return false_t;
            if (trait_of(par) != dns_t) return false_t;

            return __dns_res_count(par);
}