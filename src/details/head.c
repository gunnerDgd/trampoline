#include "head.h"
#include "dns.h"

#include "endian.h"

obj_trait head_t         = {
    .on_new   = &head_new  ,
    .on_clone = &head_clone,
    .on_ref   =           0,
    .on_del   = &head_del  ,
    .size     = sizeof(head)
};

bool_t 
    head_new
        (head* par_head, u32_t par_count, va_list par)                              {
            par_head->dns  = va_arg(par, dns*) ; if (!par_head->dns)  return false_t;
            par_head->form = par_head->dns->ptr; if (!par_head->form) return false_t;

            if (par_count == 1)             {
                par_head->dns->ptr_off += 12;
                return true_t;
            }

            par_head->form->id         = be16(va_arg(par, u16_t));
            par_head->form->flag       = be16(va_arg(par, u16_t));
            par_head->form->req        =                        0;
            par_head->form->res        =                        0;
            par_head->form->auth       =                        0;
            par_head->form->additional =                        0;
            par_head->dns->ptr_off    +=                       12;

            return true_t;
}

bool_t head_clone     (head* par, head* par_clone) { return false_t; }
void   head_del       (head* par)                  {}
u16_t  head_id        (head* par)                  { return be16(par->form->id)        ; }
u16_t  head_flag      (head* par)                  { return be16(par->form->flag)      ; }
u16_t  head_req       (head* par)                  { return be16(par->form->req)       ; }
u16_t  head_res       (head* par)                  { return be16(par->form->res)       ; }
u16_t  head_auth      (head* par)                  { return be16(par->form->auth)      ; }
u16_t  head_additional(head* par)                  { return be16(par->form->additional); }