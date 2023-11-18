#include "res.h"
#include "dns.h"

#include "endian.h"

#include <stdio.h>

obj_trait __dns_res_trait                  = {
    .init          = &__dns_res_init         ,
    .init_as_clone = &__dns_res_init_as_clone,
    .init_as_ref   =                        0,
    .deinit        = &__dns_res_deinit       ,
    .name          = &__dns_res_name         ,
    .size          = &__dns_res_size
};

bool_t 
    __dns_res_init
        (__dns_res* par_res, u32_t par_count, va_list par) {
            par_res->dns = ref(va_arg(par, __dns*));
            if (!par_res->dns)
                return false_t;

            par_res->ptr = par_res->dns->ptr_off;
            if (ptr_same(par_res->ptr, ptr_null()))
                goto __dns_res_init_failed;

            par_res->form.name = par_res->ptr;
            if (par_count == 1)              {
                if (!make_at(par_res->req, &__dns_name_trait) from (1, par_res->dns))
                    goto __dns_res_init_failed;

                par_res->form.type     = ptr_seek(par_res->form.name    , __dns_name_len(&par_res->req));
                par_res->form.cls      = ptr_seek(par_res->form.type    , 2)                            ;
                par_res->form.ttl      = ptr_seek(par_res->form.cls     , 2)                            ;
                par_res->form.data_len = ptr_seek(par_res->form.ttl     , 4)                            ;
                par_res->form.data     = ptr_seek(par_res->form.data_len, 2)                            ;

                u16_t res_len;
                ptr_rd16(par_res->form.data_len, &res_len)                          ;
                par_res->dns->ptr_off  = ptr_seek(par_res->form.data, be16(res_len));

                return true_t;
            }

            if(!make_at(par_res->req, &__dns_name_trait) from (2, par_res->dns, va_arg(par, str*)))
                goto __dns_res_init_failed;

            par_res->form.type     = ptr_seek(par_res->form.name    , __dns_name_len(&par_res->req));
            par_res->form.cls      = ptr_seek(par_res->form.type    , 2)                            ;
            par_res->form.ttl      = ptr_seek(par_res->form.cls     , 2)                            ;
            par_res->form.data_len = ptr_seek(par_res->form.ttl     , 2)                            ;
            par_res->form.data     = ptr_seek(par_res->form.data_len, 2)                            ;

            ptr_wr16(par_res->form.type, be16(va_arg(par, u16_t)));
            ptr_wr16(par_res->form.cls , be16(va_arg(par, u16_t)));
            ptr_wr16(par_res->form.ttl , be16(va_arg(par, u16_t)));

            u16_t res_data_len = va_arg(par, u16_t);
            void *res_data     = va_arg(par, void*);

            ptr_wr16 (par_res->form.data_len, be16(res_data_len))    ;
            ptr_write(par_res->form.data    , res_data, res_data_len);

            par_res->dns->ptr_off = ptr_seek(par_res->form.data, res_data_len);
            return true_t;
    __dns_res_init_failed:
            del(par_res->dns);
            return false_t;
}

bool_t 
    __dns_res_init_as_clone
        (__dns_res* par, __dns_res* par_clone) {
}

void
    __dns_res_deinit
        (__dns_res* par)  {
            del(&par->req);
            del (par->dns);
}

u64_t  
    __dns_res_size()            {
        return sizeof(__dns_res);
}

str* 
    __dns_res_name
        (__dns_res* par)             {
            return name_of(&par->req);
}

u16_t
    __dns_res_type
        (__dns_res* par)                                   {
            u16_t       ret; ptr_rd16(par->form.type, &ret);
            return be16(ret);
}

u16_t
    __dns_res_cls
        (__dns_res* par)                                  {
            u16_t       ret; ptr_rd16(par->form.cls, &ret);
            return be16(ret);
}

u16_t
    __dns_res_ttl
        (__dns_res* par)                                  {
            u16_t       ret; ptr_rd16(par->form.ttl, &ret);
            return be16(ret);
}

u64_t
    __dns_res_len
        (__dns_res* par)                                    {
            u16_t  ret; ptr_rd16(par->form.data_len, &ret)  ;
            return be16(ret) + __dns_name_len(&par->req) + 8;
}