#include "ns.h"
#include "details/ns.h"

#include "details/zone.h"
#include "details/rec.h"

#include <string.h>

obj_trait *dns_ns_t = &ns_t;

dns_rec  
    dns_ns_find
        (dns_ns par, str* par_find)                     {
            if (!par)                           return 0;
            if (!par_find)                      return 0;
            if (trait_of(par)      != dns_ns_t) return 0;
            if (trait_of(par_find) != str_t)    return 0;

            return ns_find(par, par_find);
}

dns_rec  
    dns_ns_find_cstr
        (dns_ns par, const char* par_find)                           {
            str ret_find                                             ; if (!make_at(&ret_find, str_t) from (0)) return 0;
            str_push_back_cstr(&ret_find, par_find, strlen(par_find));
            
            dns_rec ret = dns_ns_find(par, &ret_find);
            del   (&ret_find);
            return  ret;
}

dns_zone 
    dns_zone_add
        (dns_ns par, str* par_zone, dns_soa par_soa) {
            if (!par)                      return 0;
            if (trait_of(par) != dns_ns_t) return 0;

            return ns_zone_add(par, par_zone, par_soa);
}

dns_zone 
    dns_zone_add_cstr
        (dns_ns par, const char* par_zone, dns_soa par_soa)          {
            str ret_zone                                             ; if (!make_at(&ret_zone, str_t) from (0)) return 0;
            str_push_back_cstr(&ret_zone, par_zone, strlen(par_zone));

            dns_rec ret = dns_zone_add(par, &ret_zone, par_soa);
            del   (&ret_zone);
            return  ret;
}

void
    dns_zone_del
        (dns_ns par, dns_zone par_zone)          {
            if (!par)                      return;
            if (trait_of(par) != dns_ns_t) return;

            ns_zone_del(par, par_zone);
}

dns_zone 
    dns_zone_get
        (dns_ns par, str* par_str)                  {
            if (!par)                       return 0;
            if (trait_of(par) != dns_ns_t)  return 0;

            if (!par_str)                   return 0;
            if (trait_of(par_str) != str_t) return 0;

            return ns_zone_get(par, par_str);
}

dns_zone 
    dns_zone_get_cstr
        (dns_ns par, const char* par_str)                         {
            str ret_str                                           ; if (!make_at(&ret_str, str_t) from(0)) return 0;
            str_push_back_cstr(&ret_str, par_str, strlen(par_str));

            dns_zone ret = dns_zone_get(par, &ret_str);
            del    (&ret_str);
            return   ret     ;
}