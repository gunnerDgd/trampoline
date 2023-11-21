#include "req.h"
#include "dns.h"

#include "endian.h"

obj_trait __dns_req_trait                  = {
    .init          = &__dns_req_init         ,
    .init_as_clone = &__dns_req_init_as_clone,
    .init_as_ref   =                        0,
    .deinit        = &__dns_req_deinit       ,
    .name          =                        0,
    .size          = &__dns_req_size
};

bool_t 
    __dns_req_init
        (__dns_req* par_req, u32_t par_count, va_list par) {
            par_req->dns = ref(va_arg(par, __dns*));
            if (!par_req->dns)
                return false_t;

            par_req->ptr               = par_req->dns->ptr_off;
            if (null(par_req->ptr)) goto __dns_req_init_failed;

            if(par_count == 1)                                                                                                                   {
                if (null(par_req->form.name    = par_req->ptr))                                                        goto __dns_req_init_failed;
                if (null(par_req->form.type    = ptr_seek(par_req->ptr, __dns_name_len_from_ptr(par_req->form.name)))) goto __dns_req_init_failed;
                if (null(par_req->form.cls     = ptr_seek(par_req->form.type, 2)))                                     goto __dns_req_init_failed;
                if (null(par_req->dns->ptr_off = ptr_seek(par_req->form.cls , 2)))                                     goto __dns_req_init_failed;

                return true_t;
            }

            if (null(par_req->form.name = par_req->ptr)) 
                goto __dns_req_init_failed;
            
            par_req->form.type = __dns_name_to_ptr(va_arg(par, __dns_name*), par_req->form.name, par_req->dns->ptr);
            if (null(par_req->form.type))                                      goto __dns_req_init_failed;
            if (null(par_req->form.cls     = ptr_seek(par_req->form.type, 2))) goto __dns_req_init_failed;
            if (null(par_req->dns->ptr_off = ptr_seek(par_req->form.cls , 2))) goto __dns_req_init_failed;

            ptr_wr16(par_req->form.type, be16(va_arg(par, u16_t)));
            ptr_wr16(par_req->form.cls , be16(va_arg(par, u16_t)));

            return true_t;
    __dns_req_init_failed:
            del (par_req->dns);
            return false_t    ;
}

bool_t 
    __dns_req_init_as_clone
        (__dns_req* par, __dns_req* par_clone) {
            return false_t;
}

void   
    __dns_req_deinit
        (__dns_req* par)   {
            del (par->dns) ;
}

u64_t  
    __dns_req_size
        (__dns_req* par)            {
            return sizeof(__dns_req);
}