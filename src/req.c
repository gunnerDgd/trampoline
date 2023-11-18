#include "req.h"
#include "details/req.h"

obj_trait* req_t = &__dns_req_trait;

u16_t 
    dns_req_type
        (obj* par)                               {
            if(!par)                    return -1;
            if (trait_of(par) != req_t) return -1;

            return __dns_req_type(par);
}

u16_t 
    dns_req_cls
        (obj* par)                               {
            if(!par)                    return -1;
            if (trait_of(par) != req_t) return -1;

            return __dns_req_cls(par);
}

u16_t 
    dns_req_len
        (obj* par)                               {
            if(!par)                    return -1;
            if (trait_of(par) != req_t) return -1;

            return __dns_req_len(par);
}