#include "req.h"
#include "details/req.h"
#include "details/dns.h"

#include "endian.h"

u64_t
    dns_req_count
        (obj* par)                              {
            if (!par)                   return 0;
            if (trait_of(par) != dns_t) return 0;

            return head_req(&((dns*)par)->dns_head);
}

dns_req 
    dns_req_from
        (obj* par)                              {
            if (!par)                   return 0;
            if (trait_of(par) != dns_t) return 0;

            return list_begin(&((dns*)par)->req);
}

dns_req 
    dns_req_next
        (dns_req par)            {
            return list_next(par);
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
        (obj* par, str* par_str)                {
            if (!par)                   return 0;
            if (!par_str)               return 0;
            if (trait_of(par) != dns_t) return 0;

            name *ret_name = make(&name_t) from(1, par_str)            ; if(!ret_name) return 0;
            req  *ret      = make(&req_t)  from(4, par, ret_name, 1, 1);
            if  (!ret)       {
                del(ret_name);
                return 0;
            }

            return list_push_back(&((dns*)par)->req, ret);
}

dns_req 
    dns_req_cname
        (obj* par, str* par_str)                {
            if (!par)                   return 0;
            if (!par_str)               return 0;
            if (trait_of(par) != dns_t) return 0;

            name *ret_name = make(&name_t) from(1, par_str)            ; if(!ret_name) return 0;
            req  *ret      = make(&req_t)  from(4, par, ret_name, 5, 1);
            if  (!ret)       {
                del(ret_name);
                return 0;
            }

            return list_push_back(&((dns*)par)->req, ret);
}