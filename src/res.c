#include "res.h"

#include "details/res.h"
#include "details/dns.h"

#include "endian.h"

#include <stdio.h>
#include <string.h>


u16_t 
    dns_res_type
        (obj* par)                                    {
            if (!par)                        return -1;
            if (trait_of(par) != &dns_res_t) return -1;

            dns_res* ret_res = par;
            u16_t      ret          ;

            ptr_rd16   (ret_res->form.type, &ret);
            return be16(ret);
}

u16_t
    dns_res_cls
        (obj* par)                                    {
            if (!par)                        return -1;
            if (trait_of(par) != &dns_res_t) return -1;

            dns_res* ret_res = par;
            u16_t    ret          ;

            ptr_rd16   (ret_res->form.cls, &ret);
            return be16(ret);
}

u16_t 
    dns_res_ttl
        (obj* par)                                    {
            if (!par)                        return -1;
            if (trait_of(par) != &dns_res_t) return -1;

            dns_res* ret_res = par;
            u32_t    ret          ;

            ptr_rd32   (ret_res->form.ttl, &ret);
            return be32(ret);
}

obj*
    dns_res_req
        (obj* par)                                    {
            if (!par)                        return -1;
            if (trait_of(par) != &dns_res_t) return -1;

            dns_res  *ret_res = par;
            dns_name *ret     = make(&dns_name_t) from (0);
            if (!ret)                                                   return 0;
            if (!dns_name_from_ptr(ret, ret_res->form.name, ret_res->dns->ptr)) {
                del(ret_res);
                return     0;
            }

            return ret;
}

str*
    dns_res_as_a
        (obj* par)                                             {
            if (!par)                            return false_t;
            if (trait_of    (par) != &dns_res_t) return false_t;
            if (dns_res_type(par) != 1)          return false_t;
            
            dns_res *ret_res = par            ;
            str     *ret = make(str_t) from(0);

            if (!ret) return false_t;
            
            u32_t addr            ; ptr_rd32(ret_res->form.data, &addr);
            u8_t *addr_ptr = &addr; addr = be32(addr)                  ;
            char  addr_buf[32]    ;

            snprintf(addr_buf, 32, "%d.%d.%d.%d\0",
                addr_ptr[0],
                addr_ptr[1],
                addr_ptr[2],
                addr_ptr[3]
            );

            str_push_back_cstr(ret, addr_buf, 32);
            return ret;
}

obj*
    dns_res_as_cname
        (obj* par)                                       {
            if (!par)                            return 0;
            if (trait_of    (par) != &dns_res_t) return 0;
            if (dns_res_type(par) != 5)          return 0;

            dns_name *ret     = make(&dns_name_t) from(0);
            dns_res  *ret_res = par;
            
            if (!ret)                                             return false_t;
            if (!dns_name_from_ptr(ret, ret_res->form.data, ret_res->dns->ptr)) {
                del      (ret);
                return false_t;
            }

            return ret;
}

str*
    dns_res_as_cname_str
        (obj* par)                                       {
            if (!par)                            return 0;
            if (trait_of(par)     != &dns_res_t) return 0;
            if (dns_res_type(par) != 5)          return 0;

            obj* ret_name = dns_res_as_cname(par);
            if (!ret_name) return 0;

            str* ret = dns_name_to_str(ret_name);
            del (ret_name);

            return ret;
}