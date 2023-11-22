#include "cname.h"

#include "../build.h"
#include "../details/build.h"

bool_t 
    dns_build_req_cname
        (obj* par, str* par_cname, u16_t par_cls)                    {
            if (!par)                                  return false_t;
            if (trait_of(par) != &__dns_builder_trait) return false_t;

            __dns_name* name = make(&__dns_name_trait) from(0);
            if (!name)                                                        return false_t;
            if (!__dns_name_from_str(name, par_cname))       goto dns_build_req_cname_failed;
            if (!__dns_build_req    (par, name, 5, par_cls)) goto dns_build_req_cname_failed;
            
            del    (name);
            return true_t;
    dns_build_req_cname_failed:
            del     (name);
            return false_t;
}

bool_t 
    dns_build_req_cname_cstr
        (obj* par, const char* par_cname, u64_t par_len, u16_t par_cls)  {
            str ret_str;
            if (!make_at(ret_str, str_t) from(0))
                return false_t;

            str_push_back_cstr(&ret_str, par_cname, par_len);
            bool_t ret = dns_build_req_cname(par, &ret_str, par_cls);

            del(&ret_str);
            return    ret;
}

bool_t
    dns_build_res_cname
        (obj* par, obj* par_req, u16_t par_cls, u32_t par_ttl, str* par_cname) {
            if (!par)                                  return false_t;
            if (trait_of(par) != &__dns_builder_trait) return false_t;

            __dns_name *ret_cname = make (&__dns_name_trait) from (0);
            bool_t      ret;

            if (!ret_cname)                                 return false_t;
            if (!__dns_name_from_str(ret_cname, par_cname)) goto dns_build_res_cname_failed;

            ret = __dns_build_res_cname (
                par      ,
                par_req  ,
                par_cls  ,
                par_ttl  ,
                ret_cname
            );

            if (!ret) goto dns_build_res_cname_failed;
            del(ret_cname);

            return true_t;
    dns_build_res_cname_failed:
            del(ret_cname);
            return false_t;
}

bool_t 
    dns_build_res_cname_cstr
        (obj* par, obj* par_req, u16_t par_cls, u32_t par_ttl, const char* par_cname, u64_t par_len) {
            str ret_cname;
            if (!make_at(ret_cname, str_t) from(0))
                return false_t;

            bool_t ret = dns_build_res_cname (
                par        ,
                par_req   ,
                par_cls   ,
                par_ttl   ,
                &ret_cname
            );

            del(&ret_cname);
            return      ret;
}