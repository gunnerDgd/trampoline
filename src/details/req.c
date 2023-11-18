#include "req.h"
#include "dns.h"

#include "endian.h"

#include <stdio.h>

obj_trait __dns_req_trait                  = {
    .init          = &__dns_req_init         ,
    .init_as_clone = &__dns_req_init_as_clone,
    .init_as_ref   =                        0,
    .deinit        = &__dns_req_deinit       ,
    .name          = &__dns_req_name         ,
    .size          = &__dns_req_size
};

bool_t 
    __dns_req_init
        (__dns_req* par_req, u32_t par_count, va_list par) {
            par_req->dns = ref(va_arg(par, __dns*));
            if (!par_req->dns)
                return false_t;

            par_req->ptr = par_req->dns->ptr_off;
            if(ptr_same(par_req->ptr, ptr_null())) {
                del(par_req->dns);
                return false_t   ;
            }

            if(par_count == 1)                                                       {
                if (!make_at(par_req->name, &__dns_name_trait) from(1, par_req->dns))
                    goto __dns_req_init_failed;

                par_req->form.name    = par_req->ptr                                                ;
                par_req->form.type    = ptr_seek(par_req->ptr      , __dns_name_len(&par_req->name));
                par_req->form.cls     = ptr_seek(par_req->form.type, 2)                             ;
                par_req->dns->ptr_off = ptr_seek(par_req->form.cls , 2)                             ;

                return true_t;
            }

            if(!make_at(par_req->name, &__dns_name_trait) from (2, par_req->dns, va_arg (par, str*)))
                goto __dns_req_init_failed;

            par_req->form.name    = par_req->ptr                                                ;
            par_req->form.type    = ptr_seek(par_req->ptr      , __dns_name_len(&par_req->name));
            par_req->form.cls     = ptr_seek(par_req->form.type, 2)                             ;
            par_req->dns->ptr_off = ptr_seek(par_req->form.cls , 2)                             ;

            ptr_wr16(par_req->form.type, be16(va_arg(par, u16_t)));
            ptr_wr16(par_req->form.cls , be16(va_arg(par, u16_t)));

            return true_t;
    __dns_req_init_failed:
            del(par_req->dns);
            return false_t   ;
}

bool_t 
    __dns_req_init_as_clone
        (__dns_req* par, __dns_req* par_clone) {
            return false_t;
}

void   
    __dns_req_deinit
        (__dns_req* par)   {
            del(&par->name);
            del (par->dns) ;
}

u64_t  
    __dns_req_size
        (__dns_req* par)            {
            return sizeof(__dns_req);
}

str* 
    __dns_req_name
        (__dns_req* par)              {
            return name_of(&par->name);
}

u16_t  
    __dns_req_type
        (__dns_req* par)                                   {
            u16_t       ret; ptr_rd16(par->form.type, &ret);
            return be16(ret);
}

u16_t  
    __dns_req_cls
        (__dns_req* par)                                  {
            u16_t       ret; ptr_rd16(par->form.cls, &ret);
            return be16(ret);
}

u64_t  
    __dns_req_len
        (__dns_req* par)                         {
            return __dns_name_len(&par->name) + 4;
}