#include "head.h"
#include "dns.h"

#include "endian.h"

obj_trait dns_head_t                      = {
    .init          = &dns_head_init         ,
    .init_as_clone = &dns_head_init_as_clone,
    .init_as_ref   =                       0,
    .deinit        = &dns_head_deinit       ,
    .name          =                       0,
    .size          = &dns_head_size
};

bool_t 
    dns_head_init
        (dns_head* par_head, u32_t par_count, va_list par) {
            par_head->dns = va_arg(par, dns*);
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

            par_head->form->id         = be16(va_arg(par, u16_t));
            par_head->form->flag       = be16(va_arg(par, u16_t));
            par_head->form->req        =                        0;
            par_head->form->res        =                        0;
            par_head->form->auth       =                        0;
            par_head->form->additional =                        0;
            par_head->dns->ptr_off     = ptr_seek(par_head->dns->ptr_off, 12);

            return true_t;
}

bool_t 
    dns_head_init_as_clone
        (dns_head* par, dns_head* par_clone) {
            return false_t;
}

void   
    dns_head_deinit
        (dns_head* par) {
}

u64_t  
    dns_head_size()            {
        return sizeof(dns_head);
}