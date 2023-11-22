#include "cname.h"

#include "../dns.h"
#include "../details/dns.h"

#include "endian.h"

obj* 
    dns_req_cname
        (obj* par, obj* par_cname, u16_t par_cls)           {
            if (!par)                               return 0;
            if (!par_cname)                         return 0;

            if (trait_of(par)       != &dns_t)      return 0;
            if (trait_of(par_cname) != &dns_name_t) return 0;

            dns *ret_dns = par;
            obj *ret     = make(&dns_req_t) from (
                4        ,
                par      ,
                par_cname,
                5        ,
                par_cls
            );

            if (!ret) return 0;

            ret_dns->dns_head.form->req = be16(be16(ret_dns->dns_head.form->req) + 1);
            list_push_back(&ret_dns->req, ret);

            del   (ret);
            return ret ;
}

obj* 
    dns_req_cname_str
        (obj* par, str* par_cname, u16_t par_cls)      {
            if (!par)                          return 0;
            if (!par_cname)                    return 0;

            if (trait_of(par)       != &dns_t) return 0;
            if (trait_of(par_cname) !=  str_t) return 0;

            dns_name     ret_name;
            if (!make_at(ret_name, &dns_name_t) from(0))
                return 0;

            if (!dns_name_from_str(&ret_name, par_cname)) {
                del(&ret_name);
                return false_t;
            }

            obj* ret = dns_req_cname(par, &ret_name, par_cls);
            del(&ret_name);

            return ret;
}

obj* 
    dns_req_cname_cstr
        (obj* par, const char* par_cname, u64_t par_len, u16_t par_cls) {
            if (!par)                    return 0;
            if (trait_of(par) != &dns_t) return 0;

            str ret_name;
            if (!make_at(ret_name, str_t) from(0))
                return 0;

            str_push_back_cstr(&ret_name, par_cname, par_len);
            obj* ret = dns_req_cname_str(par, &ret_name, par_cls);
            del(&ret_name);

            return ret;
}

obj* 
    dns_res_cname
        (obj* par, obj* par_req, u16_t par_cls, u32_t par_ttl, obj* par_cname) {
            if (!par)                               return 0;
            if (!par_cname)                         return 0;

            if (trait_of(par)       != &dns_t)      return 0;
            if (trait_of(par_cname) != &dns_name_t) return 0;

            dns     *ret_dns = par;
            dns_res *ret     = make(&dns_res_t) from (
                7      ,
                par    ,
                par_req,
                5      ,
                par_cls,
                par_ttl,
                0      ,
                0
            );

            if (!ret) return 0;
            ptr     ret_ptr = dns_name_to_ptr(par_cname, ret->form.data, ret->dns->ptr);
            if(null(ret_ptr)) {
                del(ret);
                return 0;
            }

            ret_dns->dns_head.form->res = be16(be16(ret_dns->dns_head.form->res) + 1);
            list_push_back(&ret_dns->res, ret);

            del   (ret);
            return ret ;
}

obj* 
    dns_res_cname_str
        (obj* par, obj* par_req, u16_t par_cls, u32_t par_ttl, str* par_cname) {
            if (!par)                    return 0;
            if (trait_of(par) != &dns_t) return 0;

            dns_name ret_name;
            if (!make_at(ret_name, &dns_name_t) from(1))  return false_t;
            if (!dns_name_from_str(&ret_name, par_cname)) return false_t;

            obj* ret = dns_res_cname (
                par      ,
                par_req  ,
                par_cls  ,
                par_ttl  ,
                &ret_name
            );

            del(&ret_name);
            return ret;
}

obj* 
    dns_res_cname_cstr
        (obj* par, obj* par_req, u16_t par_cls, u32_t par_ttl, const char* par_cname, u64_t par_len) {
            if (!par)                    return 0;
            if (trait_of(par) != &dns_t) return 0;

            str ret_name;
            if (!make_at(ret_name, str_t) from(0))
                return false_t;

            obj* ret = dns_res_cname_str (
                par      ,
                par_req  ,
                par_cls  ,
                par_ttl  ,
                &ret_name
            );

            del(&ret_name);
            return ret;
}