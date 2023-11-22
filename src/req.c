#include "req.h"
#include "details/req.h"
#include "details/dns.h"

#include "endian.h"

u16_t 
    dns_req_type
        (obj* par)                                    {
            if(!par)                         return -1;
            if (trait_of(par) != &dns_req_t) return -1;

            dns_req* ret_req = par;
            u16_t    ret          ;
             
            ptr_rd16   (ret_req->form.type, &ret);
            return be16(ret);
}

u16_t 
    dns_req_cls
        (obj* par)                                    {
            if(!par)                         return -1;
            if (trait_of(par) != &dns_req_t) return -1;

            dns_req* ret_req = par;
            u16_t      ret          ;
             
            ptr_rd16   (ret_req->form.cls, &ret);
            return be16(ret);
}

u16_t 
    dns_req_len
        (obj* par)                                    {
            if(!par)                         return -1;
            if (trait_of(par) != &dns_req_t) return -1;

             dns_req* ret_req = par;
             return dns_name_len_from_ptr(ret_req->form.name) + 4;
}

obj* 
    dns_req_name
        (obj* par)                                   {
            if (!par)                        return 0;
            if (trait_of(par) != &dns_req_t) return 0;

            dns_req  *ret_req = par                       ;
            dns_name *ret     = make(&dns_name_t) from (0);

            if (!ret) return 0;
            if (!dns_name_from_ptr(ret, ret_req->form.name, ret_req->dns->ptr)) {
                del      (ret);
                return false_t;
            }

            return ret;
}

