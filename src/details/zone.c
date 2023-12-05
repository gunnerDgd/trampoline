#include "zone.h"
#include "rec.h"

obj_trait zone_t         = {
    .on_new   = &zone_new  ,
    .on_clone = &zone_clone,
    .on_ref   =           0,
    .on_del   = &zone_del  ,
    .size     = sizeof(zone)
};

bool_t 
    zone_new
        (zone* par_zone, u32_t par_count, va_list par) {
            str    *zone = va_arg(par, str*)   ;
            dns_soa soa  = va_arg(par, dns_soa);

            if (!zone)                                     return false_t;
            if (trait_of(zone) != str_t)                   return false_t;
            if (!soa)                                      return false_t;
            if (trait_of(soa) != dns_soa_t)                return false_t;
            if (!make_at(&par_zone->rec , list_t) from(0)) return false_t;
            if (!make_at(&par_zone->zone, str_t)  from(0)) return false_t;
            
            str_push_back(&par_zone->zone, zone);
            par_zone->soa = ref(soa);
            return true_t;
}

bool_t 
    zone_clone
        (zone* par, zone* par_clone) { 
            return false_t; 
}

void   
    zone_del
        (zone* par)       { 
            del(&par->rec);
            del (par->soa);
}

list_elem 
    zone_rec_add
        (zone* par, str* par_rec)                         {
            if (zone_rec_get(par, par_rec)) return false_t;
            rec* ret_rec = make(&rec_t) from (2, par, par_rec);
            if (!ret_rec) return 0;

            list_elem ret = list_push_back(&par->rec, ret_rec);
            if (!ret)       {
                del(ret_rec);
                return 0;
            }

            del   (ret_rec); ret_rec->zone = par;
            return ret     ;
}

void
    zone_rec_del
        (zone* par, list_elem par_rec)  {
            rec* rec = list_get(par_rec);
            if (!rec)                    return false_t;
            if (trait_of(rec) != &rec_t) return false_t;
            if (rec->zone != par)        return false_t;
            
            list_pop(&par->rec, par_rec);
}

list_elem
    zone_rec_get
        (zone* par, str* par_rec)          {
            list_for(&par->rec, rec_it)    {
                rec* rec = list_get(rec_it); if (!rec) return 0;
                if (str_starts(par_rec, &rec->rec))
                    return rec_it;
            }

            return 0;
}