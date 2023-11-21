#include "build.h"
#include "details/build.h"

obj_trait* dns_builder_t = &__dns_builder_trait;

obj* 
    dns_build_from
        (ptr par)                                 {
            obj* ret = make(dns_builder_t) from(0);
            if (!ret)               return false_t;
            if (!__dns_build_from(ret, par))      {
                del(ret);
                return 0;
            }

            return ret;
}

obj* 
    dns_build_from_existing
        (obj* par)                                           {
            if (!par)                          return false_t;
            if (trait_of(par) != &__dns_trait) return false_t;

            obj* ret = make(dns_builder_t) from(0);
            if (!ret)                   return false_t;
            if (!__dns_build_from_existing(ret, par)) {
                del(ret);
                return 0;
            }

            return ret;
}

bool_t 
    dns_build_head
        (obj* par, u16_t par_id, u16_t par_opcode)            {
            if (!par)                           return false_t;
            if (trait_of(par) != dns_builder_t) return false_t;

            return __dns_build_head(par, par_id, par_opcode);
}

bool_t 
    dns_build_req_a
        (obj* par, str* par_a, u16_t par_cls)                 {
            if (!par)                           return false_t;
            if (trait_of(par) != dns_builder_t) return false_t;

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
    dns_build_req_cname
        (obj* par, str* par_cname, u16_t par_cls)             {
            if (!par)                           return false_t;
            if (trait_of(par) != dns_builder_t) return false_t;

            __dns_name* name = make(&__dns_name_trait) from(0);
            if (!name)                                                    return false_t;
            if (!__dns_name_from_str(name, par_cname))   goto dns_build_req_cname_failed;
            if (!__dns_build_req(par, name, 5, par_cls)) goto dns_build_req_cname_failed;
            
            del    (name);
            return true_t;
    dns_build_req_cname_failed:
            del     (name);
            return false_t;
}

bool_t 
    dns_build_res_a
        (obj* par, str* par_req, u16_t par_cls, u32_t par_ttl, v4* par_a) {
            if (!par)                           return false_t;
            if (trait_of(par) != dns_builder_t) return false_t;

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
    dns_build_res_cname
        (obj* par, str* par_req, u16_t par_cls, u32_t par_ttl, str* par_cname) {
            if (!par)                           return false_t;
            if (trait_of(par) != dns_builder_t) return false_t;

            __dns_name *ret_cname = make (&__dns_name_trait) from (0),
                       *ret_req   = make (&__dns_name_trait) from (0);

            if (!ret_cname) return false_t;
            if (!ret_req)   return false_t;

            if (!__dns_name_from_str(ret_cname, par_cname)) goto dns_build_res_cname_failed;
            if (!__dns_name_from_str(ret_req  , par_req))   goto dns_build_res_cname_failed;

            bool_t ret = __dns_build_res_cname (
                par      ,
                ret_req  ,
                par_cls  ,
                par_ttl  ,
                ret_cname
            );

            if (!ret) goto dns_build_res_cname_failed;
            
            del(ret_req)  ;
            del(ret_cname);

            return true_t;
    dns_build_res_cname_failed:
            del(ret_req)  ;
            del(ret_cname);

            return false_t;
}

obj*
    dns_build
        (obj* par)                                            {
            if (!par)                           return false_t;
            if (trait_of(par) != dns_builder_t) return false_t;

            return __dns_build(par);
}