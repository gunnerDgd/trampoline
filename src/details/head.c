#include "head.h"
#include "dns.h"

#include "endian.h"

obj_trait __dns_head_trait                  = {
    .init          = &__dns_head_init         ,
    .init_as_clone = &__dns_head_init_as_clone,
    .init_as_ref   =                         0,
    .deinit        = &__dns_head_deinit       ,
    .name          =                         0,
    .size          = &__dns_head_size
};

bool_t 
    __dns_head_init
        (__dns_head* par_head, u32_t par_count, va_list par) {
            par_head->dns = ref(va_arg(par, __dns*));
            if (!par_head->dns)
                return false_t;

            par_head->ptr  = par_head->dns->ptr_off;
            par_head->form = ptr_raw(par_head->ptr);

            if (!par_head->form)  {
                del(par_head->dns);
                return false_t    ;
            }

            if (par_count == 1)                                              {
                par_head->dns->ptr_off = ptr_seek(par_head->dns->ptr_off, 12);
                return true_t;
            }

            par_head->form->id     = be16(va_arg(par, u16_t))            ;
            par_head->form->opcode = be16(va_arg(par, u16_t))            ;
            par_head->dns->ptr_off = ptr_seek(par_head->dns->ptr_off, 12);
            return true_t;
}

bool_t 
    __dns_head_init_as_clone
        (__dns_head* par, __dns_head* par_clone) {
            return false_t;
}

void   
    __dns_head_deinit
        (__dns_head* par) {
            del(par->dns);
}

u64_t  
    __dns_head_size() {
        return sizeof(__dns_head);
}

u16_t __dns_head_id        (__dns_head* par) { return be16(par->form->id)        ; }
u16_t __dns_head_opcode    (__dns_head* par) { return be16(par->form->opcode)    ; }
u16_t __dns_head_req       (__dns_head* par) { return be16(par->form->req)       ; }
u16_t __dns_head_res       (__dns_head* par) { return be16(par->form->res)       ; }
u16_t __dns_head_auth      (__dns_head* par) { return be16(par->form->auth)      ; }
u16_t __dns_head_additional(__dns_head* par) { return be16(par->form->additional); }