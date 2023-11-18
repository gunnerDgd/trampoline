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

            return __dns_res_type(par);
}

u16_t 
    dns_res_cls
        (obj* par)                               {
            if (!par)                   return -1;
            if (trait_of(par) != res_t) return -1;

            return __dns_res_cls(par);
}

u16_t 
    dns_res_ttl
        (obj* par)                               {
            if (!par)                   return -1;
            if (trait_of(par) != res_t) return -1;

            return __dns_res_ttl(par);
}

u16_t 
    dns_res_len
        (obj* par)                               {
            if (!par)                   return -1;
            if (trait_of(par) != res_t) return -1;

            return __dns_res_len(par);
}

bool_t 
    dns_res_as_a
        (obj* par, str* par_ret)                      {
            if (!par)                   return false_t;
            if (trait_of(par) != res_t) return false_t;

            u16_t      res_type ;
            __dns_res *res = par; ptr_rd16(res->form.type, &res_type);

            if (be16(res_type) != 1)
                return false_t;
            
            char  ret[32]  =         { 0, };
            u8_t *ret_ptr;
            u32_t ret_addr =              0; ptr_rd32(res->form.data, &ret_addr);
                  ret_addr = be32(ret_addr);
                  ret_ptr  = &ret_addr     ;
            snprintf          (ret, 32, "%d.%d.%d.%d\0",  ret_ptr[0], ret_ptr[1], ret_ptr[2], ret_ptr[3]);
            str_push_back_cstr(par_ret, ret, (strlen(ret) > 32) ? 32 : strlen(ret));

            return true_t;
}

bool_t 
    dns_res_as_aaaa
        (obj* par, str* par_ret)                      {
            if (!par)                   return false_t;
            if (trait_of(par) != res_t) return false_t;

            u16_t      res_type ;
            __dns_res *res = par; ptr_rd16(res->form.type, &res_type);

            if (be16(res_type) != 28)
                return false_t;
            
            char    ret[128] = { 0, }                 ;
            u16_t  *ret_ptr  = ptr_raw(res->form.data);
            sprintf(ret       , "%04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x\0",
                    ret_ptr[0], 
                    ret_ptr[1], 
                    ret_ptr[2], 
                    ret_ptr[3],
                    ret_ptr[4], 
                    ret_ptr[5], 
                    ret_ptr[6], 
                    ret_ptr[7]
            );

            str_push_back_cstr(par_ret, ret, 32);
            return true_t;
}

bool_t 
    dns_res_as_cname
        (obj* par, str* par_ret)                      {
            if (!par)                   return false_t;
            if (trait_of(par) != res_t) return false_t;

            u16_t      res_type      ;
            __dns_res *res = par     ; ptr_rd16(res->form.type, &res_type);
            __dns     *pkt = res->dns;

            if (be16(res_type) != 5)
                return false_t;

            u16_t   len = 0             ;
            ptr     tok = res->form.data;
            ptr_rd8(tok, &len)          ;

            while (len && !ptr_same(tok, ptr_null()))                                                 {
                if(len & (0xC0))                                                                      {
                    while(len & (0xC0))                                                               {
                        ptr_rd16(tok, &len); len = (be16(len) ^ 0xC000); tok = ptr_seek(pkt->ptr, len);
                        ptr_rd8 (tok, &len);
                    }
                    tok = ptr_seek(tok, 1);

                    str_push_back_cstr(par_ret, ptr_raw(tok), len);
                    str_push_back_cstr(par_ret, ".", 1)           ;

                    tok = ptr_seek(tok, len);
                    ptr_rd8(tok, &len)      ;
                    continue                ;
                }
                tok = ptr_seek(tok, 1);

                str_push_back_cstr(par_ret, ptr_raw(tok), len);
                str_push_back_cstr(par_ret, ".", 1)           ;

                tok = ptr_seek(tok, len);
                ptr_rd8(tok, &len)      ;
            }

            str_push_back_cstr(par_ret, "\0", 1);
            return true_t;
}