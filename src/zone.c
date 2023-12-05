#include "zone.h"
#include "details/zone.h"
#include "details/rec.h"

#include <string.h>

dns_rec 
    dns_rec_add
        (dns_zone par, str* par_rec)                {
            if (!par)                       return 0; zone* zone = list_get(par);
            if (!zone)                      return 0;
            if (trait_of(zone) != &zone_t)  return 0;

            if (!par_rec)                   return 0;
            if (trait_of(par_rec) != str_t) return 0;

            return zone_rec_add (zone, par_rec);
}

dns_rec 
    dns_rec_add_cstr
        (dns_zone par, const char* par_rec)                       {
            str ret_rec                                           ; if (!make_at(&ret_rec, str_t) from(0)) return 0;
            str_push_back_cstr(&ret_rec, par_rec, strlen(par_rec));

            dns_rec ret = dns_rec_add(par, &ret_rec); del(&ret_rec);
            return  ret;
}

void
    dns_rec_del
        (dns_zone par, dns_rec par_rec)          {
            if (!par)                      return; zone* zone = list_get(par);
            if (!zone)                     return;
            if (trait_of(zone) != &zone_t) return;
            if (!par_rec)                  return;

            zone_rec_del(zone, par_rec);
}

dns_rec 
    dns_rec_get
        (dns_zone par, str* par_rec)                {
            if (!par)                       return 0; zone* zone = list_get(par);
            if (!zone)                      return 0;
            if (trait_of(zone) != &zone_t)  return 0;

            if (!par_rec)                   return 0;
            if (trait_of(par_rec) != str_t) return 0;

            str ret_str                     ; if (!make_at(&ret_str, str_t) from(0)) return 0;
            str_push_back(&ret_str, par_rec);

            dns_rec ret = zone_rec_get(par, &ret_str); del(&ret_str);
            return  ret;
}

dns_rec 
    dns_rec_get_cstr
        (dns_zone par, const char* par_rec)                       {
            str ret_rec                                           ; if (!make_at(&ret_rec, str_t) from(0)) return 0;
            str_push_back_cstr(&ret_rec, par_rec, strlen(par_rec));

            dns_rec ret = dns_rec_get(par, &ret_rec); del(&ret_rec);
            return  ret;
}