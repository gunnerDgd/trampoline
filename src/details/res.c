#include "res.h"
#include "dns.h"

#include "endian.h"

obj_trait __dns_res_trait                  = {
    .init          = &__dns_res_init         ,
    .init_as_clone = &__dns_res_init_as_clone,
    .init_as_ref   =                        0,
    .deinit        = &__dns_res_deinit       ,
    .name          =                        0,
    .size          = &__dns_res_size
};

bool_t 
    __dns_res_init
        (__dns_res* par_res, u32_t par_count, va_list par) {
            par_res->dns = ref(va_arg(par, __dns*));
            
            if (!par_res->dns)                              return false_t            ;
            if (null(par_res->ptr = par_res->dns->ptr_off)) goto __dns_res_init_failed;

            if (par_count == 1)                                                                                                                             {
                if (null(par_res->form.name = par_res->ptr))                                                                      goto __dns_res_init_failed;
                if (null(par_res->form.type     = ptr_seek(par_res->form.name    , __dns_name_len_from_ptr(par_res->form.name)))) goto __dns_res_init_failed;
                if (null(par_res->form.cls      = ptr_seek(par_res->form.type    , 2)))                                           goto __dns_res_init_failed;
                if (null(par_res->form.ttl      = ptr_seek(par_res->form.cls     , 2)))                                           goto __dns_res_init_failed;
                if (null(par_res->form.data_len = ptr_seek(par_res->form.ttl     , 4)))                                           goto __dns_res_init_failed;
                if (null(par_res->form.data     = ptr_seek(par_res->form.data_len, 2)))                                           goto __dns_res_init_failed;

                u16_t res_len;
                if (null(ptr_rd16(par_res->form.data_len, &res_len))) goto __dns_res_init_failed;
                par_res->dns->ptr_off  = ptr_seek(par_res->form.data, be16(res_len));

                return true_t;
            }

            if (null(par_res->form.name = par_res->ptr))                                                   
                goto __dns_res_init_failed;
            if (null(par_res->form.type = __dns_name_to_ptr(va_arg(par, __dns_name*), par_res->form.name, par_res->dns->ptr)))
                goto __dns_res_init_failed;

            if (null(par_res->form.cls      = ptr_seek(par_res->form.type    , 2))) goto __dns_res_init_failed;
            if (null(par_res->form.ttl      = ptr_seek(par_res->form.cls     , 2))) goto __dns_res_init_failed;
            if (null(par_res->form.data_len = ptr_seek(par_res->form.ttl     , 4))) goto __dns_res_init_failed;
            if (null(par_res->form.data     = ptr_seek(par_res->form.data_len, 2))) goto __dns_res_init_failed;

            ptr_wr16(par_res->form.type, be16(va_arg(par, u16_t)));
            ptr_wr16(par_res->form.cls , be16(va_arg(par, u16_t)));
            ptr_wr16(par_res->form.ttl , be16(va_arg(par, u16_t)));

            u16_t data_len = va_arg(par, u16_t);
            void *data     = va_arg(par, void*);

            ptr_wr16 (par_res->form.data_len,  be16(data_len));
            ptr_write(par_res->form.data    , data, data_len) ;

            par_res->dns->ptr_off = ptr_seek(par_res->form.data, data_len);
            return true_t;
    __dns_res_init_failed:
            del(par_res->dns);
            return false_t;
}

bool_t 
    __dns_res_init_as_clone
        (__dns_res* par, __dns_res* par_clone) {
            return false_t;
}

void
    __dns_res_deinit
        (__dns_res* par)  {
            del (par->dns);
}

u64_t  
    __dns_res_size()            {
        return sizeof(__dns_res);
}