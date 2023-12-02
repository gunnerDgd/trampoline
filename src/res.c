#include "res.h"
#include "details/res.h"
#include "details/req.h"
#include "details/dns.h"

#include "endian.h"

#include <stdio.h>
#include <string.h>

u64_t
    dns_res_count
        (obj* par)                              {
            if (!par)                   return 0;
            if (trait_of(par) != dns_t) return 0;

            return head_res(&((dns*)par)->dns_head);
}

dns_req 
    dns_res_from
        (obj* par)                              {
            if (!par)                   return 0;
            if (trait_of(par) != dns_t) return 0;

            return list_begin(&((dns*)par)->res);
}

dns_req 
    dns_res_next
        (dns_req par)                       {
            dns_req ret = list_next(par)    ;
            return (list_get(ret)) ? ret : 0;
}

u16_t 
    dns_res_type
        (dns_res par)                                 {
            if (!par)                        return -1; res* par_res = list_get(par);
            if (!par_res)                    return -1;
            if (trait_of(par_res) != &res_t) return -1;
            return res_type(par_res);
}

u16_t 
    dns_res_cls
        (dns_res par)                                 {
            if (!par)                        return -1; res* par_res = list_get(par);
            if (!par_res)                    return -1;
            if (trait_of(par_res) != &res_t) return -1;
            return res_cls(par_res);
}

u32_t 
    dns_res_ttl
        (dns_res par)                                 {
            if (!par)                        return -1; res* par_res = list_get(par);
            if (!par_res)                    return -1;
            if (trait_of(par_res) != &res_t) return -1;
            return res_ttl(par_res);
}

str*
    dns_res_req
        (obj* par)                                   {
            if (!par)                        return 0; res* par_res = list_get(par);
            if (!par_res)                    return 0;
            if (trait_of(par_res) != &res_t) return 0;

            name *ret_name = res_req(par_res);
            if  (!ret_name) return false_t;

            str*   ret = name_as_str(ret_name); del(ret_name);
            return ret;
}

str*
    dns_res_as_a
        (dns_res par)                                {
            if (!par)                        return 0; res* par_res = list_get(par);
            if (!par_res)                    return 0;
            if (trait_of(par_res) != &res_t) return 0;
            if (dns_res_type(par) != 1)      return 0;

            str *ret = make(str_t) from (0);
            if (!ret) return 0;

            u8_t    *addr = par_res->form.data;
            char     addr_buf [32];
            snprintf(addr_buf, 32, "%d.%d.%d.%d\0",
                (u32_t)addr[0],
                (u32_t)addr[1],
                (u32_t)addr[2],
                (u32_t)addr[3]
            );

            str_push_back_cstr(ret, addr_buf, 32);
            return ret;
}

str*
    dns_res_as_cname
        (dns_res par)                                {
            if (!par)                        return 0; res* par_res = list_get(par);
            if (!par_res)                    return 0;
            if (trait_of(par_res) != &res_t) return 0;
            if (dns_res_type(par) != 5)      return 0;

            name *ret_name = make(&name_t) from (2, par_res->dns, par_res->form.data);
            if  (!ret_name) return 0;

            str*   ret = name_as_str(ret_name); del(ret_name);
            return ret;
}

dns_res 
    dns_res_a
        (obj* par, dns_req par_req, u32_t par_ttl, v4* par_a) {
            if (!par)                            return 0;
            if (!par_req)                        return 0;
            if (!par_a)                          return 0;
            if (trait_of(par)         != dns_t)  return 0; req* req = list_get(par_req);
            if (trait_of(req)         != &req_t) return 0;
            if (dns_req_type(par_req) != 1)      return 0;

            u32_t ret_addr = be32(v4_addr(par_a));
            res*  ret      = make (&res_t) from  (
                7        ,
                par      ,
                req      ,
                1        ,
                1        ,
                par_ttl  ,
                4        ,
                &ret_addr
            );

            if(!ret)    {
                del(ret);
                return 0;
            }

            return list_push_back(&((dns*)par)->res, ret);
}

dns_res 
    dns_res_cname
        (obj* par, dns_req par_req, u32_t par_ttl, str* par_cname) {
            if (!par)                            return 0;
            if (!par_req)                        return 0;
            if (!par_cname)                      return 0;
            if (trait_of(par)         != dns_t)  return 0; req* req = list_get(par_req);
            if (trait_of(req)         != &req_t) return 0;
            if (dns_req_type(par_req) != 5)      return 0;

            name *ret_name = make (&name_t) from (1, par_cname); if (!ret_name) return 0;
            res  *ret      = make (&res_t)  from (
                7                 ,
                par               ,
                req               ,
                5                 ,
                1                 ,
                par_ttl           ,
                name_len(ret_name),
                name_ptr(ret_name)
            );

            if (!ret)        {
                del(ret_name);
                del(ret)     ;
                return      0;
            }

            del(ret_name);
            return list_push_back(&((dns*)par)->res, ret);
}