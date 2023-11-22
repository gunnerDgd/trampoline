#include "res.h"
#include "req.h"
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
    __dns_res_from
        (__dns_res* par) {
                if (null(par->form.name = par->dns->ptr_off))                                                         return false_t;
                if (null(par->form.type     = ptr_seek(par->form.name    , __dns_name_len_from_ptr(par->form.name)))) return false_t;
                if (null(par->form.cls      = ptr_seek(par->form.type    , 2)))                                       return false_t;
                if (null(par->form.ttl      = ptr_seek(par->form.cls     , 2)))                                       return false_t;
                if (null(par->form.data_len = ptr_seek(par->form.ttl     , 4)))                                       return false_t;
                if (null(par->form.data     = ptr_seek(par->form.data_len, 2)))                                       return false_t;

                u16_t data_len;
                if (null(ptr_rd16(par->form.data_len, &data_len)))
                    return false_t;

                par->dns->ptr_off = ptr_seek(par->form.data, be16(data_len));
                return true_t;
}

bool_t 
    __dns_res_from_param
        (__dns_res* par, struct __dns_req* par_req, u16_t par_type, u16_t par_cls, u32_t par_ttl, u16_t par_len, void* par_data) {
            if(null(par->form.name = par->dns->ptr_off)) 
                return false_t;

            u16_t req = ptr_dist(par_req->form.name, par->dns->ptr);
                  req = be16    (req | 0xC000)                     ;
            if (null(par->form.type     = ptr_wr16(par->form.name    , req)))      return false_t;
            if (null(par->form.cls      = ptr_wr16(par->form.type    , par_type))) return false_t;
            if (null(par->form.ttl      = ptr_wr16(par->form.cls     , par_cls)))  return false_t;
            if (null(par->form.data_len = ptr_wr32(par->form.ttl     , par_ttl)))  return false_t;
            if (null(par->form.data     = ptr_wr16(par->form.data_len, par_len)))  return false_t;
                        
            par->dns->ptr_off = ptr_write(par->form.data, par_data, par_len);
            return true_t;
}

bool_t 
    __dns_res_init
        (__dns_res* par_res, u32_t par_count, va_list par) {
            par_res->dns = ref(va_arg(par, __dns*));
            switch(par_count)                {
            case 1:                          {
                if(!__dns_res_from(par_res)) {
                    del(par_res->dns);
                    return    false_t;
                }

                break;
            }
            case 7:                                          {
                __dns_req* par_req  = va_arg(par, __dns_req*);
                u16_t      par_type = va_arg(par, u16_t)     ;
                u16_t      par_cls  = va_arg(par, u16_t)     ;
                u32_t      par_ttl  = va_arg(par, u32_t)     ;
                u16_t      par_len  = va_arg(par, u16_t)     ;
                void*      par_data = va_arg(par, void*)     ;

                bool_t ret = __dns_res_from_param (
                    par_res ,
                    par_req ,
                    par_type,
                    par_cls ,
                    par_ttl ,
                    par_len ,
                    par_data
                );

                if (!ret)            {
                    del(par_res->dns);
                    return    false_t;
                }

                break;
            }
            default:
                del(par_res->dns);
                return    false_t;
            }

            return true_t;
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