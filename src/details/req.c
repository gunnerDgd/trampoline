#include "req.h"
#include "pkt.h"

#include "endian.h"

obj_trait req_t         = {
    .on_new   = &req_new  ,
    .on_clone = &req_clone,
    .on_ref   =          0,
    .on_del   = &req_del  ,
    .size     = sizeof(req)
};

bool_t
    req_new_from
        (req* par)                            {
            par->form.name = par->pkt->ptr_off;
            u8_t  *ptr     = par->pkt->ptr_off;
            while(*ptr)            {
                if ((*ptr) & 0xC0) { ptr += 1; break; }
                if ((*ptr + par->pkt->ptr_off) > (par->pkt->ptr + box_size(par->pkt->box)))
                    return false_t;

                ptr += ((*ptr) + 1);
            }

            par->form.type    = ptr            + 1;
            par->form.cls     = par->form.type + 1;
            par->pkt->ptr_off = par->form.cls  + 1;
            return true_t;
}

bool_t 
    req_new_from_par
        (req* par, name* par_name, u16_t par_type, u16_t par_cls) {
            if(head_res(&par->pkt->dns_head))
                return false_t;

            par->form.name = par->pkt->ptr_off;
            if ((par->pkt->ptr_off + name_len(par_name) + 4) > (par->pkt->ptr + box_size(par->pkt->box)))
                return false_t;

            mem_copy(par->form.name, name_ptr(par_name)   , name_len(par_name))   ; 
            par->form.type               = par->form.name + name_len(par_name)    ;
            par->form.cls                = par->form.type                     + 1 ;
            par->pkt->dns_head.form->req = be16(head_req(&par->pkt->dns_head) + 1);
            par->pkt->ptr_off            = par->form.cls                      + 1 ;
            
            *par->form.type = be16(par_type);
            *par->form.cls  = be16(par_cls) ;

            return true_t;
}

bool_t 
    req_new
        (req* par_req, u32_t par_count, va_list par) {
            par_req->pkt = va_arg(par, pkt*);
            if (!par_req->pkt)                     return false_t;
            if (trait_of (par_req->pkt) != &pkt_t) return false_t;

            if (!par_req->pkt)  return false_t               ;
            if (par_count == 1) return req_new_from (par_req);
            if (par_count == 4)                              {
                name* par_name = va_arg(par, name*);
                u16_t par_type = va_arg(par, u16_t);
                u16_t par_cls  = va_arg(par, u16_t);

                if (!par_name)                     return false_t;
                if (trait_of(par_name) != &name_t) return false_t;

                return req_new_from_par (
                    par_req , 
                    par_name, 
                    par_type, 
                    par_cls
                );
            }

            return false_t;
}

bool_t req_clone(req* par, req* par_clone) { return false_t; }
void   req_del  (req* par)                 { }

name*  req_name (req* par) { return make(&name_t) from (2, par->pkt, par->form.name); }
u16_t  req_type (req* par) { return be16(*par->form.type); }
u16_t  req_cls  (req* par) { return be16(*par->form.cls) ; }