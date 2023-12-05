#include "res.h"
#include "req.h"
#include "pkt.h"

#include "endian.h"

obj_trait res_t         = {
    .on_new   = &res_new  ,
    .on_clone = &res_clone,
    .on_ref   =          0,
    .on_del   = &res_del  ,
    .size     = sizeof(res)
};

bool_t 
    res_new_from
        (res* par)                            {
            par->form.name = par->pkt->ptr_off;
            u8_t  *ptr     = par->pkt->ptr_off;
            while(*ptr)            {
                if ((*ptr) & 0xC0) { ptr += 1; break; }
                if ((*ptr + par->pkt->ptr_off) > (par->pkt->ptr + box_size(par->pkt->box)))
                    return false_t;

                ptr += ((*ptr) + 1);
            }

            par->form.type     = ptr                +                 1;
            par->form.cls      = par->form.type     +                 1;
            par->form.ttl      = par->form.cls      +                 1;
            par->form.data_len = par->form.ttl      +                 1;
            par->form.data     = par->form.data_len +                 1;
            par->pkt->ptr_off  = par->form.data     + res_data_len(par);
            
            return true_t;
}

bool_t 
    res_new_from_par
        (res* par, u16_t par_type, u16_t par_cls, u32_t par_ttl, u16_t par_len, u8_t* par_data) {
            *par->form.type     = be16(par_type); par->form.cls      = par->form.type     + 1;
            *par->form.cls      = be16(par_cls) ; par->form.ttl      = par->form.cls      + 1;
            *par->form.ttl      = be32(par_ttl) ; par->form.data_len = par->form.ttl      + 1;
            *par->form.data_len = be16(par_len) ; par->form.data     = par->form.data_len + 1;

            mem_copy(par->form.data, par_data, par_len);
            par->pkt->ptr_off              = (par->form.data + par_len);
            return true_t;
}

bool_t 
    res_new
        (res* par_res, u32_t par_count, va_list par)  {
            par_res->pkt       = va_arg(par, pkt*)    ; if(!par_res->pkt) return false_t;
            par_res->form.name = par_res->pkt->ptr_off;

            if (par_count == 1) return res_new_from(par_res);
            if (par_count == 7)                             {
                obj*  par_obj  = va_arg(par, obj*) ;
                u16_t par_type = va_arg(par, u16_t);
                u16_t par_cls  = va_arg(par, u16_t);
                u32_t par_ttl  = va_arg(par, u32_t);
                u16_t par_len  = va_arg(par, u16_t);
                void* par_data = va_arg(par, void*);

                u16_t name;
                if       (trait_of(par_obj) == &req_t) {
                    req* req = par_obj; 
                    if  (req->pkt != par_res->pkt)
                        return false_t;

                    name = be16(0xC000 | (req->form.name - par_res->pkt->ptr));
                }

                else if  (trait_of(par_obj) == &res_t) {
                    res* res = par_obj;
                    if  (res->pkt != par_res->pkt)
                        return false_t;

                    name = be16(0xC000 | (res->form.data - par_res->pkt->ptr));
                }
                else return false_t;

                par_res->form.type = par_res->form.name + 2; *((u16_t*)par_res->form.name) = name;
                return res_new_from_par (
                    par_res ,
                    par_type,
                    par_cls ,
                    par_ttl ,
                    par_len ,
                    par_data
                );
            }

            return false_t;
}

bool_t res_clone(res* par, res* par_clone) { return false_t; }
void   res_del  (res* par)                 {  }

name*  res_req     (res* par) { return make(&name_t) from (2, par->pkt, par->form.name); }
u16_t  res_type    (res* par) { return be16(*par->form.type)    ; }
u16_t  res_cls     (res* par) { return be16(*par->form.cls)     ; }
u32_t  res_ttl     (res* par) { return be32(*par->form.ttl)     ; }
u16_t  res_data_len(res* par) { return be16(*par->form.data_len); }