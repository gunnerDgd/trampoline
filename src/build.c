#include "build.h"
#include "details/build.h"

obj_trait* dns_builder_t = &__dns_builder_trait;

bool_t 
    dns_build_head
        (dns_builder* par, u16_t par_id, u16_t par_opcode)    {
            if (!par)                           return false_t;
            if (trait_of(par) != dns_builder_t) return false_t;

            return __dns_build_head(par, par_id, par_opcode);
}

bool_t 
    dns_build_req
        (dns_builder* par, str* par_req, u16_t par_type, u16_t par_cls) {
            if (!par)                           return false_t;
            if (trait_of(par) != dns_builder_t) return false_t;

            return __dns_build_req(par, par_req, par_type, par_cls);
}

bool_t 
    dns_build_res
        (dns_builder* par, str* par_req, u16_t par_type, u16_t par_cls, u16_t par_ttl, str* par_res) {
            if (!par)                           return false_t;
            if (trait_of(par) != dns_builder_t) return false_t;

            return __dns_build_res(par, par_req, par_type, par_cls, par_ttl, par_res);
}

dns* 
    dns_build
        (dns_builder* par)                                    {
            if (!par)                           return false_t;
            if (trait_of(par) != dns_builder_t) return false_t;

            return __dns_build(par);
}