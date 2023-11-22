#include "a.h"

#include "../dns.h"
#include "../details/dns.h"

#include "endian.h"

obj* 
    dns_req_a
        (obj* par, obj* par_a, u16_t par_cls)                 {
            if (!par)                           return false_t;
            if (!par_a)                         return false_t;
            if (trait_of(par)   != &dns_t)      return false_t;
            if (trait_of(par_a) != &dns_name_t) return false_t;

            dns* ret_dns = par;
            obj* ret     = make (&dns_req_t) from (
                4      ,
                par    ,
                par_a  ,
                1      ,
                par_cls
            );

            if (!ret) return 0;

            ret_dns->dns_head.form->req = be16(be16(ret_dns->dns_head.form->req) + 1);
            list_push_back(&ret_dns->req, ret);

            del   (ret);
            return ret ;
}

obj* 
    dns_req_a_str
        (obj* par, str* par_a, u16_t par_cls)            {
            if (!par)                      return false_t;
            if (!par_a)                    return false_t;
            if (trait_of(par)   != &dns_t) return false_t;
            if (trait_of(par_a) !=  str_t) return false_t;

            dns_name ret_name;
            if (!make_at(ret_name, &dns_name_t) from(0)) return false_t;
            if (!dns_name_from_str(&ret_name, par_a))    return false_t;

            obj* ret = dns_req_a(par, &ret_name, par_cls);
            del(&ret_name);

            return ret;
}

obj* 
    dns_req_a_cstr
        (obj* par, const char* par_a, u64_t par_len, u16_t par_cls) {
            if (!par)                    return false_t;
            if (trait_of(par) != &dns_t) return false_t;

            str ret_name;
            if (!make_at(ret_name, str_t) from(0)) 
                return false_t;

            str_push_back_cstr(&ret_name, par_a, par_len);
            obj* ret = dns_req_a_str(par, &ret_name, par_cls);
            del(&ret_name);

            return ret;
}

obj* 
    dns_res_a
        (obj* par, obj* par_req, u16_t par_cls, u32_t par_ttl, v4* par_addr) {
            if (!par)                            return false_t;
            if (!par_req)                        return false_t;
            if (trait_of(par)     != &dns_t)     return false_t;
            if (trait_of(par_req) != &dns_req_t) return false_t;

            dns  *ret_dns  = par                       ;
            u32_t ret_addr = be32(v4_addr(par_addr, 0));
            obj  *ret      = make (&dns_res_t) from    (
                7        ,
                par      ,
                par_req  ,
                1        ,
                par_cls  ,
                par_ttl  ,
                4        ,
                &par_addr
            );

            if (!ret) return 0;

            ret_dns->dns_head.form->res = be16(be16(ret_dns->dns_head.form->res) + 1);
            list_push_back(&ret_dns->res, ret);

            del   (ret);
            return ret ;
}

obj* 
    dns_res_a_cstr
        (obj* par, obj* par_req, u16_t par_cls, u32_t par_ttl, const char* par_a) {
            if (!par)                            return false_t;
            if (!par_req)                        return false_t;
            if (trait_of(par)     != &dns_t)     return false_t;
            if (trait_of(par_req) != &dns_req_t) return false_t;

            v4 ret_addr;
            if (!make_at(ret_addr, v4_t) from(2, par_a, 0))
                return false_t;

            obj* ret = dns_res_a(par, par_req, par_cls, par_ttl, &ret_addr);
            del(&ret_addr);

            return ret;
}