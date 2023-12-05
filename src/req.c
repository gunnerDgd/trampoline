 #include "req.h"
#include "pkt.h"

#include "details/req.h"
#include "details/pkt.h"

#include "endian.h"

#include <stdio.h>
#include <string.h>

dns_req 
    dns_pkt_req
        (dns_pkt par)                               {
            if (!par)                       return 0;
            if (trait_of(par) != dns_pkt_t) return 0;

            return list_begin(&((pkt*)par)->req);
}

u64_t
    dns_req_count
        (dns_pkt par)                               {
            if (!par)                       return 0;
            if (trait_of(par) != dns_pkt_t) return 0;

            return head_req(&((pkt*)par)->dns_head);
}

dns_req 
    dns_req_next
        (dns_req par)                                        {
            if (!par)                                return 0; req* par_req = list_get(par);
            if (!par_req)                            return 0;
            if (trait_of(par_req) != &req_t)         return 0;

            par = list_next(par);
            if (par == list_end(&par_req->pkt->req)) return 0;

            return par;
}

u16_t 
    dns_req_type
        (dns_req par)                                 {
            if (!par)                        return -1; req* par_req = list_get(par);
            if (!par_req)                    return -1;
            if (trait_of(par_req) != &req_t) return -1;

            return req_type(par_req);
}

u16_t 
    dns_req_cls
        (dns_req par)                                 {
            if (!par)                        return -1; req* par_req = list_get(par);
            if (!par_req)                    return -1;
            if (trait_of(par_req) != &req_t) return -1;

            return req_cls(par_req);
}

str*
    dns_req_name
        (dns_req par)                                {
            if (!par)                        return 0; req* par_req = list_get(par);
            if (!par_req)                    return 0;
            if (trait_of(par_req) != &req_t) return 0;

            name* ret_name = req_name(par_req);
            if  (!ret_name) return 0;

            str*   ret = name_as_str(ret_name); del(ret_name);
            return ret;
}

dns_req 
    dns_req_a
        (dns_pkt par, str* par_str)                 {
            if (!par)                       return 0;
            if (!par_str)                   return 0;
            if (trait_of(par) != dns_pkt_t) return 0;

            name *ret_req_name = make(&name_t) from(1, par_str)                ; if(!ret_req_name) return 0;
            req  *ret_req      = make(&req_t)  from(4, par, ret_req_name, 1, 1);
            if  (!ret_req)       {
                del(ret_req_name);
                return 0;
            }

            dns_req ret = list_push_back(&((pkt*)par)->req, ret_req);
            del    (ret_req);
            return  ret;
}

dns_req 
    dns_req_a_cstr
        (dns_pkt par, const char* par_str)                     {
            str *ret_a = make (str_t) from (0)                 ; if (!ret_a) return 0;
            str_push_back_cstr(ret_a, par_str, strlen(par_str));

            dns_req ret = dns_req_a(par, ret_a); del(ret_a);
            return  ret;
}

dns_req 
    dns_req_cname
        (dns_pkt par, str* par_str)                    {
            if (!par)                       return 0;
            if (!par_str)                   return 0;
            if (trait_of(par) != dns_pkt_t) return 0;

            name *ret_req_name = make(&name_t) from(1, par_str)                ; if(!ret_req_name) return 0;
            req  *ret_req      = make(&req_t)  from(4, par, ret_req_name, 5, 1);
            if  (!ret_req)       {
                del(ret_req_name);
                return 0;
            }

            dns_req ret = list_push_back(&((pkt*)par)->req, ret_req);
            del    (ret_req);
            return  ret;
}

dns_req 
    dns_req_cname_cstr
        (dns_pkt par, const char* par_str)                         {
            str *ret_cname = make (str_t) from (0)                 ; if (!ret_cname) return 0;
            str_push_back_cstr(ret_cname, par_str, strlen(par_str));

            dns_req ret = dns_req_cname(par, ret_cname); del(ret_cname);
            return  ret;
}

dns_req 
    dns_req_ptr
        (dns_pkt par, v4* par_v4) {
            u32_t ret_ptr_addr = v4_addr(par_v4);
            char  ret_ptr [64] = { 0, };

            snprintf(ret_ptr, 32, "%d.%d.%d.%d.in-addr.arpa\0",
                    (ret_ptr_addr & 0xFF000000) >> 24,
                    (ret_ptr_addr & 0x00FF0000) >> 16,
                    (ret_ptr_addr & 0x0000FF00) >> 8 ,
                    (ret_ptr_addr & 0x000000FF)
            );

            return dns_req_ptr_cstr(par, ret_ptr);
}

dns_req 
    dns_req_ptr_str
        (dns_pkt par, str* par_ptr)                     {
            if (!par)                           return 0;
            if (!par_ptr)                       return 0;
            if (trait_of(par)     != dns_pkt_t) return 0;
            if (trait_of(par_ptr) != str_t)     return 0;

            if(!str_ends_cstr(par_ptr, ".in-addr.arpa", 13))
                str_push_back_cstr(par_ptr, ".in-addr.arpa", 13);

            name *ret_req_ptr = make(&name_t) from (1, par_ptr); if (!ret_req_ptr) return 0;
            req  *ret_req     = make(&req_t)  from (4, par, ret_req_ptr, 12, 1);
            if  (!ret_req)      {
                del(ret_req_ptr);
                return         0;
            }

            dns_req ret = list_push_back(&((pkt*)par)->req, ret_req);
            del    (ret_req);
            return  ret;
            
}

dns_req 
    dns_req_ptr_cstr
        (dns_pkt par, const char* par_ptr) {
             str ret_ptr;
             if (!make_at(&ret_ptr, str_t) from(0))
                 return false_t;

             dns_req ret = dns_req_ptr_str(par, &ret_ptr); del(&ret_ptr);
             return  ret;
}

dns_req 
    dns_req_soa
        (dns_pkt par, str* par_str)                    {
            if (!par)                       return 0;
            if (!par_str)                   return 0;
            if (trait_of(par) != dns_pkt_t) return 0;

            name *ret_req_name = make(&name_t) from(1, par_str)                ; if(!ret_req_name) return 0;
            req  *ret_req      = make(&req_t)  from(4, par, ret_req_name, 6, 1);
            if  (!ret_req)       {
                del(ret_req_name);
                return 0;
            }

            dns_req ret = list_push_back(&((pkt*)par)->req, ret_req);
            del    (ret_req);
            return  ret;
}

dns_req 
    dns_req_soa_cstr
        (dns_pkt par, const char* par_soa)                       {
            str *ret_soa = make (str_t) from (0)                 ; if (!ret_soa) return 0;
            str_push_back_cstr(ret_soa, par_soa, strlen(par_soa));

            dns_req ret = dns_req_soa(par, ret_soa); del(ret_soa);
            return  ret;
}