#include "rslv_req.h"
#include "details/rslv_req.h"

str* 
    dns_rslv_req_name
        (dns_rslv_req par)                           {
            if (!par)                         return 0;
            if (trait_of(par) != &rslv_req_t) return 0;
            return rslv_req_name(par);
}

u16_t
    dns_rslv_req_type
        (dns_rslv_req par)                           {
            if (!par)                         return 0;
            if (trait_of(par) != &rslv_req_t) return 0;
            return rslv_req_type(par);
}

u16_t
    dns_rslv_req_cls
        (dns_rslv_req par)                           {
            if (!par)                         return 0;
            if (trait_of(par) != &rslv_req_t) return 0;
            return rslv_req_cls(par);
}

bool_t
    dns_rslv_next
        (dns_rslv_req par)                                  {
            if (!par)                         return false_t;
            if (trait_of(par) != &rslv_req_t) return false_t;

            return rslv_next(par);
}

task
    dns_rslv_res
        (dns_rslv_req par)                           {
            if (!par)                         return 0;
            if (trait_of(par) != &rslv_req_t) return 0;
            return rslv_res(par);
}


dns_res 
    dns_rslv_a
        (dns_rslv_req par, u32_t par_ttl, v4* par_res) {
            if (!par)                         return 0;
            if (trait_of(par) != &rslv_req_t) return 0;
            return rslv_a (
                par    ,
                par_ttl,
                par_res
            );
}

dns_res 
    dns_rslv_a_str
        (dns_rslv_req par, u32_t par_ttl, str* par_res) {
            if (!par)                         return 0;
            if (trait_of(par) != &rslv_req_t) return 0;
            return rslv_a_str (
                par    ,
                par_ttl,
                par_res
            );
}

dns_res 
    dns_rslv_a_cstr
        (dns_rslv_req par, u32_t par_ttl, const char* par_res) {
            if (!par)                         return 0;
            if (trait_of(par) != &rslv_req_t) return 0;
            return rslv_a_cstr (
                par    ,
                par_ttl,
                par_res
            );
}

dns_res 
    dns_rslv_cname
        (dns_rslv_req par, u32_t par_ttl, str* par_res) {
            if (!par)                         return 0;
            if (trait_of(par) != &rslv_req_t) return 0;
            return rslv_cname (
                par    ,
                par_ttl,
                par_res
            );
}

dns_res 
    dns_rslv_cname_cstr
        (dns_rslv_req par, u32_t par_ttl, const char* par_res) {
            if (!par)                         return 0;
            if (trait_of(par) != &rslv_req_t) return 0;
            return rslv_cname_cstr (
                par    ,
                par_ttl,
                par_res
            );
}

dns_res
    dns_rslv_soa
        (dns_rslv_req par, u32_t par_ttl, dns_soa par_soa) {
            if (!par)                         return 0;
            if (trait_of(par) != &rslv_req_t) return 0;
            return rslv_soa (
                par    ,
                par_ttl,
                par_soa
            );
}

dns_res
    dns_rslv_ptr       
        (dns_rslv_req par, u32_t par_ttl, str* par_ptr) {
            if (!par)                         return 0;
            if (trait_of(par) != &rslv_req_t) return 0;
            return rslv_ptr (
                par    ,
                par_ttl,
                par_ptr
            );
}

dns_res
    dns_rslv_ptr_cstr 
        (dns_rslv_req par, u32_t par_ttl, const char* par_ptr) {
            if (!par)                         return 0;
            if (trait_of(par) != &rslv_req_t) return 0;
            return rslv_ptr_cstr (
                par    ,
                par_ttl,
                par_ptr
            );
}

dns_res 
    dns_rslv_auth_a
        (dns_rslv_req par, u32_t par_ttl, v4* par_res) {
            if (!par)                         return 0;
            if (trait_of(par) != &rslv_req_t) return 0;
            return rslv_auth_a (
                par    ,
                par_ttl,
                par_res
            );
}

dns_res 
    dns_rslv_auth_a_str
        (dns_rslv_req par, u32_t par_ttl, str* par_res) {
            if (!par)                         return 0;
            if (trait_of(par) != &rslv_req_t) return 0;
            return rslv_auth_a_str (
                par    ,
                par_ttl,
                par_res
            );
}

dns_res 
    dns_rslv_auth_a_cstr
        (dns_rslv_req par, u32_t par_ttl, const char* par_res) {
            if (!par)                         return 0;
            if (trait_of(par) != &rslv_req_t) return 0;
            return rslv_auth_a_cstr (
                par    ,
                par_ttl,
                par_res
            );
}

dns_res 
    dns_rslv_auth_cname
        (dns_rslv_req par, u32_t par_ttl, str* par_res) {
            if (!par)                         return 0;
            if (trait_of(par) != &rslv_req_t) return 0;
            return rslv_auth_cname (
                par    ,
                par_ttl,
                par_res
            );
}

dns_res 
    dns_rslv_auth_cname_cstr
        (dns_rslv_req par, u32_t par_ttl, const char* par_res) {
            if (!par)                         return 0;
            if (trait_of(par) != &rslv_req_t) return 0;
            return rslv_auth_cname_cstr (
                par    ,
                par_ttl,
                par_res
            );
}

dns_res
    dns_rslv_auth_soa
        (dns_rslv_req par, u32_t par_ttl, dns_soa par_soa) {
            if (!par)                         return 0;
            if (trait_of(par) != &rslv_req_t) return 0;
            return rslv_auth_soa (
                par    ,
                par_ttl,
                par_soa
            );
}

dns_res
    dns_rslv_auth_ptr
        (dns_rslv_req par, u32_t par_ttl, str* par_ptr) {
            if (!par)                         return 0;
            if (trait_of(par) != &rslv_req_t) return 0;
            return rslv_auth_ptr (
                par    ,
                par_ttl,
                par_ptr
            );
}

dns_res
    dns_rslv_auth_ptr_cstr
        (dns_rslv_req par, u32_t par_ttl, const char* par_ptr) {
            if (!par)                         return 0;
            if (trait_of(par) != &rslv_req_t) return 0;
            return rslv_auth_ptr_cstr (
                par    ,
                par_ttl,
                par_ptr
            );
}