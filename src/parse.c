#include "parse.h"
#include "details/parse.h"

obj_trait* dns_parser_t = &__dns_parser_trait;

obj* 
    dns_parse_from
        (ptr par)                       {
            if(null(par)) return false_t;
    
            __dns_parser* ret = make (dns_parser_t) from (0);
            if (!ret) return false_t;

            ret->dns = make (&__dns_trait) from (0);
            if (!ret->dns) return false_t;

            ret->dns->ptr     = par;
            ret->dns->ptr_off = par;
            return ret;
}

void 
    dns_parse_req
        (obj* par, u16_t par_type, u16_t par_cls)    {
            if (!par)                          return;
            if (trait_of(par) != dns_parser_t) return;

            __dns_parse_req(par, par_type, par_cls);
}

void 
    dns_parse_res
        (obj* par, u16_t par_type, u16_t par_cls, str* par_name)           {
            if (!par)                                                return;
            if (trait_of(par) != dns_parser_t)                       return;

            __dns_name* name = make(&__dns_name_trait) from(0);
            if (!name)                  return false_t;
            if (!__dns_name_from_str(name, par_name)) {
                del(name);
                return   ;
            }
            
            __dns_parse_res(par, par_type, par_cls, name);
}

obj* 
    dns_parse
        (obj* par)                                     {
            if (!par)                          return 0;
            if (trait_of(par) != dns_parser_t) return 0;

            return __dns_parse(par);
}