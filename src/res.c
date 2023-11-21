#include "res.h"

#include "details/res.h"
#include "details/dns.h"

#include "endian.h"

#include <stdio.h>
#include <string.h>

obj_trait* res_t = &__dns_res_trait;

u16_t 
    dns_res_type
        (obj* par)                               {
            if (!par)                   return -1;
            if (trait_of(par) != res_t) return -1;

            __dns_res* ret_res = par;
            u16_t      ret          ;

            ptr_rd16   (ret_res->form.type, &ret);
            return be16(ret);
}

u16_t 
    dns_res_cls
        (obj* par)                               {
            if (!par)                   return -1;
            if (trait_of(par) != res_t) return -1;

            __dns_res* ret_res = par;
            u16_t      ret          ;

            ptr_rd16   (ret_res->form.cls, &ret);
            return be16(ret);
}

u16_t 
    dns_res_ttl
        (obj* par)                               {
            if (!par)                   return -1;
            if (trait_of(par) != res_t) return -1;

            __dns_res* ret_res = par;
            u32_t      ret          ;

            ptr_rd32   (ret_res->form.ttl, &ret);
            return be32(ret);
}

u16_t 
    dns_res_len
        (obj* par)                               {
            if (!par)                   return -1;
            if (trait_of(par) != res_t) return -1;

            __dns_res* ret = par;
            return __dns_name_len_from_ptr(ret->form.name) +
                     dns_res_data_len     (par)            + 
                    10;
}

obj*
    dns_res_req
        (obj* par)                               {
            if (!par)                   return -1;
            if (trait_of(par) != res_t) return -1;

            __dns_res  *ret_res = par;
            __dns_name *ret     = make(&__dns_name_trait) from (0);
            if (!ret)                                                     return 0;
            if (!__dns_name_from_ptr(ret, ret_res->form.name, ret_res->dns->ptr)) {
                del(ret_res);
                return     0;
            }

            return ret;
}

u64_t  
    dns_res_data_len
        (obj* par)                               {
            if (!par)                   return -1;
            if (trait_of(par) != res_t) return -1;

            __dns_res *ret_res = par;
            u16_t      ret          ;

            ptr_rd16   (ret_res->form.data_len, &ret);
            return be16(ret);
}

str*
    dns_res_as_a
        (obj* par)                                        {
            if (!par)                       return false_t;
            if (trait_of    (par) != res_t) return false_t;
            if (dns_res_type(par) != 1)     return false_t;
            
            __dns_res *ret_res = par            ;
            str       *ret = make(str_t) from(0);

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
        (obj* par)                                        {
            if (!par)                       return false_t;
            if (trait_of    (par) != res_t) return false_t;
            if (dns_res_type(par) != 5)     return false_t;

            __dns_name *ret     = make(&__dns_name_trait) from(0);
            __dns_res  *ret_res = par;
            
            if (!ret)                                               return false_t;
            if (!__dns_name_from_ptr(ret, ret_res->form.data, ret_res->dns->ptr)) {
                del      (ret);
                return false_t;
            }

            return ret;
}