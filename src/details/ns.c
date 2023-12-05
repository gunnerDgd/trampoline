#include "ns.h"
#include "zone.h"
#include "rec.h"
#include "soa.h"

obj_trait ns_t         = {
    .on_new   = &ns_new  ,
    .on_clone = &ns_clone,
    .on_ref   =         0,
    .on_del   = &ns_del  ,
    .size     = sizeof(ns)
};

bool_t ns_new  (ns* par_ns, u32_t par_count, va_list par) { return make_at(&par_ns->zone, list_t) from(0); }
bool_t ns_clone(ns* par   , ns* par_clone)                { return false_t; }
void   ns_del  (ns* par)                                  { del(par); }

list_elem 
    ns_zone_add
        (ns* par, str* par_str, dns_soa par_soa) {
            zone *ret_zone = make (&zone_t) from (2, par_str, par_soa);
            if  (!ret_zone) return 0;

            list_elem ret = list_push_back(&par->zone, ret_zone);
            if(!ret)          {
                del (ret_zone);
                return 0;
            }

            del   (ret_zone); ret_zone->ns = par;
            return ret      ;
}

void      
    ns_zone_del
        (ns* par, list_elem par_elem)      {
            zone *zone = list_get(par_elem);
            if  (!zone)                     return;
            if  (trait_of(zone) != &zone_t) return;
            if  (zone->ns != par)           return;

            list_pop(&par->zone, par_elem);
}

list_elem
    ns_zone_get
        (ns* par, str* par_zone)              {
            list_for(&par->zone, zone_it)     {
                zone* zone = list_get(zone_it); if (!zone) continue;
                u64_t tok     = str_find_cstr(par_zone, 0, ".", 1)     ;
                u64_t tok_off = str_find     (par_zone, 0, &zone->zone);

                if ((tok + 1) == tok_off)
                    return zone_it;
            }

            return zone_it;
}

list_elem 
    ns_find
        (ns* par, str* par_find)          {
            str find                      ;  if (!make_at(&find, str_t) from(0)) return false_t;
            str_push_back(&find, par_find);

            list_elem zone_find = ns_zone_get(par, &find); if(!zone_find) goto find_failed;
            zone     *zone      = list_get(zone_find)    ; if(!zone)      goto find_failed;

            str_pop_back(&find, str_len(&zone->zone));
            list_elem ret = zone_rec_get(zone, &find); if (!ret) goto find_failed;
            del(&find);
            return ret;
    find_failed:
            del(&find);
            return   0;
}