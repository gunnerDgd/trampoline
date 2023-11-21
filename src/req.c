#include "req.h"
#include "details/req.h"

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

