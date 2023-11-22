#include "req.h"
#include "dns.h"

#include "endian.h"

obj_trait dns_req_t                      = {
    .init          = &dns_req_init         ,
    .init_as_clone = &dns_req_init_as_clone,
    .init_as_ref   =                      0,
    .deinit        = &dns_req_deinit       ,
    .name          =                      0,
    .size          = &dns_req_size
};

bool_t 
    dns_req_do_init_from
        (dns_req* par)                          {
            if (null(par->form.name = par->ptr))
                return false_t;
            if (null(par->form.type = ptr_seek(par->ptr, dns_name_len_from_ptr(par->form.name))))
                return false_t;

            if (null(par->form.cls     = ptr_seek(par->form.type, 2))) return false_t;
            if (null(par->dns->ptr_off = ptr_seek(par->form.cls , 2))) return false_t;

            return true_t;
}
bool_t 
    dns_req_do_init_from_param
        (dns_req* par_req, va_list par)                                {
            dns_name* name = va_arg(par, dns_name*);
            if (!name)                                   return false_t;
            if (trait_of(name) != &dns_name_t)           return false_t;
            if (null(par_req->form.name = par_req->ptr)) return false_t;
            
            par_req->form.type = dns_name_to_ptr (name, par_req->form.name, par_req->dns->ptr);
            if (null(par_req->form.type))                                      return false_t;
            if (null(par_req->form.cls     = ptr_seek(par_req->form.type, 2))) return false_t;
            if (null(par_req->dns->ptr_off = ptr_seek(par_req->form.cls , 2))) return false_t;

            ptr_wr16(par_req->form.type, be16(va_arg(par, u16_t)));
            ptr_wr16(par_req->form.cls , be16(va_arg(par, u16_t)));

            return true_t;
}

bool_t 
    dns_req_init
        (dns_req* par_req, u32_t par_count, va_list par) {
            par_req->dns = va_arg(par, dns*);
            if (!par_req->dns)
                return false_t;

            par_req->ptr = par_req->dns->ptr_off;
            if (null(par_req->ptr)) 
                goto init_failed;

            switch(par_count) {
            case 1: 
                if (!dns_req_do_init_from(par_req))
                    goto init_failed;
                break;
            case 4: 
                if (!dns_req_do_init_from_param(par_req, par)) 
                    goto init_failed;
                break;
            }
            
            return true_t;
    init_failed:
            del (par_req->dns);
            return false_t    ;
}

bool_t 
    dns_req_init_as_clone
        (dns_req* par, dns_req* par_clone) {
            return false_t;
}

void   
    dns_req_deinit
        (dns_req* par)   {
}

u64_t  
    dns_req_size
        (dns_req* par)            {
            return sizeof(dns_req);
}