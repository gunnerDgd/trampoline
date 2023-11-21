#include "req.h"
#include "details/req.h"
#include "details/dns.h"

#include "endian.h"

obj_trait* req_t = &__dns_req_trait;

u16_t 
    dns_req_type
        (obj* par)                               {
            if(!par)                    return -1;
            if (trait_of(par) != req_t) return -1;

            __dns_req* ret_req = par;
            u16_t      ret          ;
             
            ptr_rd16   (ret_req->form.type, &ret);
            return be16(ret);
}

u16_t 
    dns_req_cls
        (obj* par)                               {
            if(!par)                    return -1;
            if (trait_of(par) != req_t) return -1;

            __dns_req* ret_req = par;
            u16_t      ret          ;
             
            ptr_rd16   (ret_req->form.cls, &ret);
            return be16(ret);
}

u16_t 
    dns_req_len
        (obj* par)                               {
            if(!par)                    return -1;
            if (trait_of(par) != req_t) return -1;

             __dns_req* ret_req = par;
             return __dns_name_len_from_ptr(ret_req->form.name) + 4;
}

obj* 
    dns_req_name
        (obj* par)                              {
            if (!par)                   return 0;
            if (trait_of(par) != req_t) return 0;

            __dns_req  *ret_req = par                             ;
            __dns_name *ret     = make(&__dns_name_trait) from (0);

            if (!ret) return 0;
            if (!__dns_name_from_ptr(ret, ret_req->form.name, ret_req->dns->ptr)) {
                del      (ret);
                return false_t;
            }

            return ret;
}

