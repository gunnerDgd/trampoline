#include "soa.h"
#include <endian.h>

obj_trait soa_t         = {
    .on_new   = &soa_new  ,
    .on_clone = &soa_clone,
    .on_ref   =          0,
    .on_del   = &soa_del  ,
    .size     = sizeof(soa)
};

bool_t 
    soa_new_from
        (soa* par, res* par_res)             {
            if (be16(par_res->form.type) != 6)                                            return false_t;
            if (!make_at(&par->mname, &name_t) from(2, par_res->pkt, par_res->form.data)) return false_t;
            if (!make_at(&par->rname, &name_t) from(2, par_res->pkt, par_res->form.data)) return false_t;

            u32_t *ptr   = par_res->form.data + name_len(&par->mname) + name_len(&par->rname);
            par->serial  = be32(*ptr++);
            par->refresh = be32(*ptr++);
            par->retry   = be32(*ptr++);
            par->expire  = be32(*ptr++);
            par->ttl     = be32(*ptr++);

            return true_t;
}

bool_t 
    soa_new
        (soa* par_soa, u32_t par_count, va_list par)                          {
            if(par_count == 1) return soa_new_from(par_soa, va_arg(par, res*));
            str*  mname   = va_arg(par, str*) ; if(!mname || trait_of(mname) != str_t) return false_t;
            str*  rname   = va_arg(par, str*) ; if(!rname || trait_of(rname) != str_t) return false_t;

            if (!make_at(&par_soa->mname, &name_t) from(1, mname)) return false_t;
            if (!make_at(&par_soa->rname, &name_t) from(1, rname)) return false_t;
                        
            par_soa->serial  = be32(va_arg(par, u32_t));
            par_soa->refresh = be32(va_arg(par, u32_t));
            par_soa->retry   = be32(va_arg(par, u32_t));
            par_soa->expire  = be32(va_arg(par, u32_t));
            par_soa->ttl     = be32(va_arg(par, u32_t));

            return true_t;
}

bool_t 
    soa_clone
        (soa* par, soa* par_clone) {
            return false_t;
}

void
    soa_del
        (soa* par)          {
            del(&par->mname);
            del(&par->rname);
}