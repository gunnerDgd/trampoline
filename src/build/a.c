#include "../build.h"
#include "../details/build.h"

#include "a.h"
#include <string.h>

bool_t 
    dns_build_req_a
        (obj* par, str* par_a, u16_t par_cls)                        {
            if (!par)                                  return false_t;
            if (trait_of(par) != &__dns_builder_trait) return false_t;

            __dns_name* name = make(&__dns_name_trait) from(0);
            if (!name)                                                    return false_t;
            if (!__dns_name_from_str(name, par_a))           goto dns_build_req_a_failed;
            if (!__dns_build_req    (par, name, 1, par_cls)) goto dns_build_req_a_failed;
            
            del    (name);
            return true_t;
    dns_build_req_a_failed:
            del     (name);
            return false_t;
}

bool_t 
    dns_build_req_a_cstr
        (obj* par, const char* par_a, u64_t par_len, u16_t par_cls) {
            str ret_str;
            if (!make_at(ret_str, str_t) from(0))
                return false_t;

            str_push_back_cstr(&ret_str, par_a, par_len)         ;
            bool_t ret = dns_build_req_a (par, &ret_str, par_cls);

            del(&ret_str);
            return    ret;
}

bool_t 
    dns_build_res_a
        (obj* par, str* par_req, u16_t par_cls, u32_t par_ttl, v4* par_a) {
            if (!par)                                  return false_t;
            if (trait_of(par) != &__dns_builder_trait) return false_t;

            __dns_name *ret_name = make (&__dns_name_trait) from (0);
            if (!ret_name)
                return false_t;

            bool_t ret = __dns_build_res_a (
                par              ,
                ret_name         ,
                par_cls          ,
                par_ttl          ,
                v4_addr(par_a, 0)
            );

            if(!ret)          {
                del (ret_name);
                return false_t;
            }

            del(ret_name);
            return true_t;
}

bool_t
    dns_build_res_a_cstr
        (obj* par, const char* par_req, u64_t par_len, u16_t par_cls, u32_t par_ttl, v4* par_v4) {
            str ret_str;
            if (!make_at(ret_str, str_t) from(0))
                return false_t;

            str_push_back_cstr(&ret_str, par_req, par_len);
            bool_t ret = dns_build_res_a(par, &ret_str, par_cls, par_ttl, par_v4);

            del(&ret_str);
            return    ret;
}