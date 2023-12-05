#include "rec.h"
#include "zone.h"

#include <endian.h>

obj_trait rec_t         = {
    .on_new   = &rec_new  ,
    .on_clone = &rec_clone,
    .on_del   = &rec_del  ,
    .size     = sizeof(rec)
};

obj_trait rdata_t          = {
    .on_new   = &rdata_new   ,
    .on_clone = &rdata_clone ,
    .on_ref   = 0            ,
    .on_del   = &rdata_del   ,
    .size     = sizeof(rdata),
};

bool_t 
    rdata_new
        (rdata* par_rec, u32_t par_count, va_list par) {
            par_rec->type = be16(va_arg(par, u64_t));
            par_rec->cls  = be16(va_arg(par, u64_t));
            par_rec->ttl  = be32(va_arg(par, u64_t));
            par_rec->pri  = be16(va_arg(par, u64_t));

            obj* data = va_arg(par, obj*);
            if (trait_of(data) == str_t) if (!clone_at(&par_rec->str, data)) return false_t;
            if (trait_of(data) == v4_t)  if (!clone_at(&par_rec->v4 , data)) return false_t;

            return true_t;
}

bool_t 
    rdata_clone
        (rdata* par, rdata* par_clone) {
            return false_t;
}

void   
    rdata_del
        (rdata* par)   {
            del(&par->obj);
}

bool_t 
    rec_new
        (rec* par_rec, u32_t par_count, va_list par)                    {
            par_rec->zone = va_arg(par, zone*);
            str* rec      = va_arg(par, str*) ;
            if (!rec)                                     return false_t;
            if (trait_of(rec) != str_t)                   return false_t;
            if (!make_at(&par_rec->rec , str_t)  from(0)) return false_t;
            if (!make_at(&par_rec->data, list_t) from(0)) return false_t;

            str_push_back     (&par_rec->rec, rec)   ;
            str_push_back_cstr(&par_rec->rec, ".", 1);

            return true_t;
    new_failed:
            del(&par_rec->rec) ;
            del(&par_rec->data);
            return false_t;
}

bool_t 
    rec_clone
        (rec* par, rec* par_clone) { 
            return false_t; 
}

void
    rec_del
        (rec* par)         {
            del(&par->rec) ;
            del(&par->data);
}