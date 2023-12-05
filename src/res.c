#include "res.h"
#include "pkt.h"

#include "details/res.h"
#include "details/req.h"
#include "details/pkt.h"
#include "details/soa.h"

#include "endian.h"

#include <stdio.h>
#include <string.h>

dns_req 
    dns_pkt_res
        (dns_pkt par)                                  {
            if (!par)                       return 0;
            if (trait_of(par) != dns_pkt_t) return 0;

            return list_begin(&((pkt*)par)->res);
}

dns_req 
    dns_pkt_auth_res
        (dns_pkt par)                                  {
            if (!par)                       return 0;
            if (trait_of(par) != dns_pkt_t) return 0;

            return list_begin(&((pkt*)par)->auth);
}

u64_t
    dns_res_count
        (dns_pkt par)                                  {
            if (!par)                       return 0;
            if (trait_of(par) != dns_pkt_t) return 0;

            return head_res(&((pkt*)par)->dns_head);
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
        (dns_pkt par)                                   {
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

            name *ret_name = make(&name_t) from (2, par_res->pkt, par_res->form.data);
            if  (!ret_name) return 0;

            str*   ret = name_as_str(ret_name); del(ret_name);
            return ret;
}

str*
    dns_res_as_ptr
        (dns_res par)                                {
            if (!par)                        return 0; res* par_res = list_get(par);
            if (!par_res)                    return 0;
            if (trait_of(par_res) != &res_t) return 0;

            name *ret_name = make(&name_t) from (2, par_res->pkt, par_res->form.data);
            if  (!ret_name) return 0;

            str*   ret = name_as_str(ret_name); del(ret_name);
            return ret;
}

dns_soa 
    dns_res_as_soa
        (dns_res par)                                {
            if (!par)                        return 0; res* par_res = list_get(par);
            if (!par_res)                    return 0;
            if (trait_of(par_res) != &res_t) return 0;

            return make (&soa_t) from (1, par_res);
}

dns_res 
    dns_res_a
        (dns_pkt par, dns_req par_req, u32_t par_ttl, v4* par_a) {
            if (!par)                                return 0;
            if (!par_req)                            return 0;
            if (!par_a)                              return 0;
            if (trait_of(par)         != dns_pkt_t)  return 0; req* req = list_get(par_req);
            if (trait_of(req)         != &req_t)     return 0;

            u32_t ret_res_addr = be32(v4_addr(par_a));
            res*  ret_res      = make (&res_t) from  (
                7            ,
                par          ,
                req          ,
                1            ,
                1            ,
                par_ttl      ,
                4            ,
                &ret_res_addr
            );

            if(!ret_res)    {
                del(ret_res);
                return 0;
            }

            ret_res->pkt->dns_head.form->res   = be16(head_res(&ret_res->pkt->dns_head) + 1);
            ret_res->pkt->dns_head.form->flag |= 0x0080;

            dns_res ret = list_push_back(&((pkt*)par)->res, ret_res);
            del    (ret_res);
            return  ret;
}

dns_res 
    dns_res_a_str
        (dns_pkt par, dns_req par_req, u32_t par_ttl, str* par_a)      {
            v4  *ret_addr = make(v4_t) from (2, str_ptr(par_a), 0); 
            if (!ret_addr) 
                return 0;

            dns_res ret = dns_res_a(par, par_req, par_ttl, ret_addr); del (ret_addr);
            return  ret;
}

dns_res 
    dns_res_a_cstr
        (dns_pkt par, dns_req par_req, u32_t par_ttl, const char* par_a) {
            v4  *ret_addr = make(v4_t) from (2, par_a, 0); 
            if (!ret_addr)
                return 0;

            dns_res ret = dns_res_a(par, par_req, par_ttl, ret_addr); del (ret_addr);
            return  ret;
}

dns_res 
    dns_res_cname
        (dns_pkt par, dns_req par_req, u32_t par_ttl, str* par_cname) {
            if (!par)                       return 0;
            if (!par_req)                   return 0;
            if (!par_cname)                 return 0;
            if (trait_of(par) != dns_pkt_t) return 0; req* req = list_get(par_req);
            if (trait_of(req) != &req_t)    return 0;

            name *ret_res_name = make (&name_t) from (1, par_cname); if (!ret_res_name) return 0;
            res  *ret_res      = make (&res_t)  from (
                7                     ,
                par                   ,
                req                   ,
                5                     ,
                1                     ,
                par_ttl               ,
                name_len(ret_res_name),
                name_ptr(ret_res_name)
            );

            if (!ret_res)        {
                del(ret_res_name);
                del(ret_res)     ;
                return          0;
            }

            ret_res->pkt->dns_head.form->res   = be16(head_res(&ret_res->pkt->dns_head) + 1);
            ret_res->pkt->dns_head.form->flag |= 0x0080;

            del(ret_res_name);
            dns_res ret = list_push_back(&((pkt*)par)->res, ret_res);
            del    (ret_res);
            return  ret     ;
}

dns_res 
    dns_res_cname_cstr
        (dns_pkt par, dns_req par_req, u32_t par_ttl, const char* par_cname) {
            str *ret_cname = make(str_t) from (0);
            if (!ret_cname)
                return 0;

            str_push_back_cstr(ret_cname, par_cname, strlen(par_cname))  ;
            dns_res ret = dns_res_cname(par, par_req, par_ttl, ret_cname); del(ret_cname);
            return  ret;
}

dns_res 
    dns_res_ptr
        (dns_pkt par, dns_req par_req, u32_t par_ttl, str* par_ptr) {
            if (!par)                           return 0;
            if (!par_ptr)                       return 0;
            if (trait_of(par)     != dns_pkt_t) return 0;
            if (trait_of(par_ptr) != str_t)     return 0; req* req = list_get(par_req);
            if (trait_of(req)     != &req_t)    return 0;
            
            name *ret_res_name = make(&name_t) from (1, par_ptr);
            res  *ret_res      = make(&res_t)  from (
                7                     ,
                par                   ,
                req                   ,
                12                    ,
                1                     ,
                par_ttl               ,
                name_len(ret_res_name),
                name_ptr(ret_res_name)
            );

            ret_res->pkt->dns_head.form->res   = be16(head_res(&ret_res->pkt->dns_head) + 1);
            ret_res->pkt->dns_head.form->flag |= 0x0080;

            del(ret_res_name);
            dns_res ret = list_push_back(&((pkt*)par)->res, ret_res);
            del    (ret_res);
            return  ret     ;
}

dns_res 
    dns_res_ptr_cstr
        (dns_pkt par, dns_req par_req, u32_t par_ttl, const char* par_ptr) {
            str *ret_ptr = make(str_t) from (0);
            if (!ret_ptr)
                return 0;

            str_push_back_cstr(ret_ptr, par_ptr, strlen(par_ptr))    ;
            dns_res ret = dns_res_ptr(par, par_req, par_ttl, ret_ptr); del(ret_ptr);
            return  ret;
}

dns_res 
    dns_res_soa
        (dns_pkt par, dns_req par_req, u32_t par_ttl, dns_soa par_soa) {
            if (!par)                           return 0;
            if (!par_soa)                       return 0;
            if (trait_of(par)     != dns_pkt_t) return 0;
            if (trait_of(par_soa) != dns_soa_t) return 0; req* req = list_get(par_req);
            if (trait_of(req)     != &req_t)    return 0;
            
            soa  *ret_soa      = par_soa                                                   ;
            u64_t ret_buf_size = name_len(&ret_soa->mname) + name_len(&ret_soa->rname) + 20;
            u8_t *ret_buf      = mem_new (0, ret_buf_size)                                 ; if (!ret_buf) return false_t;
            
            u8_t* ptr = ret_buf;
            mem_copy(ptr, name_ptr(&ret_soa->mname), name_len(&ret_soa->mname)); ptr += name_len(&ret_soa->mname);
            mem_copy(ptr, name_ptr(&ret_soa->rname), name_len(&ret_soa->rname)); ptr += name_len(&ret_soa->rname);
            mem_copy(ptr, &ret_soa->serial, 20);

            res  *ret_res = make (&res_t) from (
                7           ,
                par         ,
                req         ,
                6           ,
                1           ,
                par_ttl     ,
                ret_buf_size,
                ret_buf
            );

            ret_res->pkt->dns_head.form->res   = be16(head_res(&ret_res->pkt->dns_head) + 1);
            ret_res->pkt->dns_head.form->flag |= 0x0080;

            dns_res ret = list_push_back(&((pkt*)par)->res, ret_res);
            del    (ret_res); mem_del(0, ret_buf);
            return  ret     ;
}

// Authoritive Answer

dns_res 
    dns_auth_res_a
        (dns_pkt par, dns_req par_req, u32_t par_ttl, v4* par_a) {
            if (!par)                                return 0;
            if (!par_req)                            return 0;
            if (!par_a)                              return 0;
            if (trait_of(par)         != dns_pkt_t)  return 0; req* req = list_get(par_req);
            if (trait_of(req)         != &req_t)     return 0;
            if (dns_req_type(par_req) != 1)          return 0;

            u32_t ret_res_addr = be32(v4_addr(par_a));
            res*  ret_res      = make (&res_t) from  (
                7            ,
                par          ,
                req          ,
                1            ,
                1            ,
                par_ttl      ,
                4            ,
                &ret_res_addr
            );

            if(!ret_res)    {
                del(ret_res);
                return 0;
            }

            ret_res->pkt->dns_head.form->auth  = be16(head_auth(&ret_res->pkt->dns_head) + 1);
            ret_res->pkt->dns_head.form->flag |= 0x0080;

            dns_res ret = list_push_back(&((pkt*)par)->auth, ret_res);
            del    (ret_res);
            return  ret;
}

dns_res 
    dns_auth_res_a_str
        (dns_pkt par, dns_req par_req, u32_t par_ttl, str* par_a)      {
            v4  *ret_addr = make(v4_t) from (2, str_ptr(par_a), 0); 
            if (!ret_addr) 
                return 0;

            dns_res ret = dns_auth_res_a(par, par_req, par_ttl, ret_addr); del (ret_addr);
            return  ret;
}

dns_res 
    dns_auth_res_a_cstr
        (dns_pkt par, dns_req par_req, u32_t par_ttl, const char* par_a) {
            v4  *ret_addr = make(v4_t) from (2, par_a, 0); 
            if (!ret_addr)
                return 0;

            dns_res ret = dns_auth_res_a(par, par_req, par_ttl, ret_addr); del (ret_addr);
            return  ret;
}

dns_res 
    dns_auth_res_cname
        (dns_pkt par, dns_req par_req, u32_t par_ttl, str* par_cname) {
            if (!par)                       return 0;
            if (!par_req)                   return 0;
            if (!par_cname)                 return 0;
            if (trait_of(par) != dns_pkt_t) return 0; req* req = list_get(par_req);
            if (trait_of(req) != &req_t)    return 0;

            name *ret_res_name = make (&name_t) from (1, par_cname); if (!ret_res_name) return 0;
            res  *ret_res      = make (&res_t)  from (
                7                     ,
                par                   ,
                req                   ,
                5                     ,
                1                     ,
                par_ttl               ,
                name_len(ret_res_name),
                name_ptr(ret_res_name)
            );

            if (!ret_res)        {
                del(ret_res_name);
                del(ret_res)     ;
                return          0;
            }

            ret_res->pkt->dns_head.form->auth  = be16(head_auth(&ret_res->pkt->dns_head) + 1);
            ret_res->pkt->dns_head.form->flag |= 0x0080;

            del(ret_res_name);
            dns_res ret = list_push_back(&((pkt*)par)->auth, ret_res);
            del    (ret_res);
            return  ret     ;
}

dns_res 
    dns_auth_res_cname_cstr
        (dns_pkt par, dns_req par_req, u32_t par_ttl, const char* par_cname) {
            str *ret_cname = make(str_t) from (0);
            if (!ret_cname)
                return 0;

            str_push_back_cstr(ret_cname, par_cname, strlen(par_cname))  ;
            dns_res ret = dns_auth_res_cname(par, par_req, par_ttl, ret_cname); del(ret_cname);
            return  ret;
}

dns_res 
    dns_auth_res_ptr
        (dns_pkt par, dns_req par_req, u32_t par_ttl, str* par_ptr) {
            if (!par)                           return 0;
            if (!par_ptr)                       return 0;
            if (trait_of(par)     != dns_pkt_t) return 0;
            if (trait_of(par_ptr) != str_t)     return 0; req* req = list_get(par_req);
            if (trait_of(req)     != &req_t)    return 0;
            
            name *ret_res_name = make(&name_t) from (1, par_ptr);
            res  *ret_res      = make(&res_t)  from (
                7                     ,
                par                   ,
                req                   ,
                12                    ,
                1                     ,
                par_ttl               ,
                name_len(ret_res_name),
                name_ptr(ret_res_name)
            );

            ret_res->pkt->dns_head.form->auth  = be16(head_auth(&ret_res->pkt->dns_head) + 1);
            ret_res->pkt->dns_head.form->flag |= 0x0080;

            del(ret_res_name);
            dns_res ret = list_push_back(&((pkt*)par)->auth, ret_res);
            del    (ret_res);
            return  ret     ;
}

dns_res 
    dns_auth_res_ptr_cstr
        (dns_pkt par, dns_req par_req, u32_t par_ttl, const char* par_ptr) {
            str *ret_ptr = make(str_t) from (0);
            if (!ret_ptr)
                return 0;

            str_push_back_cstr(ret_ptr, par_ptr, strlen(par_ptr))    ;
            dns_res ret = dns_auth_res_ptr(par, par_req, par_ttl, ret_ptr); del(ret_ptr);
            return  ret;
}

dns_res 
    dns_auth_res_soa
        (dns_pkt par, dns_req par_req, u32_t par_ttl, dns_soa par_soa) {
            if (!par)                           return 0;
            if (!par_soa)                       return 0;
            if (trait_of(par)     != dns_pkt_t) return 0;
            if (trait_of(par_soa) != dns_soa_t) return 0; req* req = list_get(par_req);
            if (trait_of(req)     != &req_t)    return 0;
            
            soa  *ret_soa      = par_soa                                                   ;
            u64_t ret_buf_size = name_len(&ret_soa->mname) + name_len(&ret_soa->rname) + 20;
            u8_t *ret_buf      = mem_new (0, ret_buf_size)                                 ; if (!ret_buf) return false_t;
            
            u8_t* ptr = ret_buf;
            mem_copy(ptr, name_ptr(&ret_soa->mname), name_len(&ret_soa->mname)); ptr += name_len(&ret_soa->mname);
            mem_copy(ptr, name_ptr(&ret_soa->rname), name_len(&ret_soa->rname)); ptr += name_len(&ret_soa->rname);
            mem_copy(ptr, &ret_soa->serial, 20);

            res  *ret_res = make (&res_t) from (
                7           ,
                par         ,
                req         ,
                6           ,
                1           ,
                par_ttl     ,
                ret_buf_size,
                ret_buf
            );

            ret_res->pkt->dns_head.form->auth  = be16(head_auth(&ret_res->pkt->dns_head) + 1);
            ret_res->pkt->dns_head.form->flag |= 0x0080;

            dns_res ret = list_push_back(&((pkt*)par)->auth, ret_res);
            del    (ret_res); mem_del(0, ret_buf);
            return  ret     ;
}