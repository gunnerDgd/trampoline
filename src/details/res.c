#include "res.h"
#include "req.h"
#include "dns.h"

#include "endian.h"

obj_trait dns_res_t                      = {
    .init          = &dns_res_init         ,
    .init_as_clone = &dns_res_init_as_clone,
    .init_as_ref   =                      0,
    .deinit        = &dns_res_deinit       ,
    .name          =                      0,
    .size          = &dns_res_size
};

bool_t 
    dns_res_do_init_from
        (dns_res* par) {
            if (null(par->form.name = par->dns->ptr_off))                                                       return false_t;
            if (null(par->form.type     = ptr_seek(par->form.name    , dns_name_len_from_ptr(par->form.name)))) return false_t;
            if (null(par->form.cls      = ptr_seek(par->form.type    , 2)))                                     return false_t;
            if (null(par->form.ttl      = ptr_seek(par->form.cls     , 2)))                                     return false_t;
            if (null(par->form.data_len = ptr_seek(par->form.ttl     , 4)))                                     return false_t;
            if (null(par->form.data     = ptr_seek(par->form.data_len, 2)))                                     return false_t;

            u16_t data_len;
            if (null(ptr_rd16(par->form.data_len, &data_len)))
                return false_t;

            par->dns->ptr_off = ptr_seek(par->form.data, be16(data_len));
            return true_t;
}

bool_t 
    dns_res_do_init_from_param
        (dns_res* par_res, va_list par)                       {
            if(null(par_res->form.name = par_res->dns->ptr_off))
                return false_t;

            dns_req* par_req  = va_arg(par, dns_req*);
            u16_t    par_type = va_arg(par, u16_t)   ;
            u16_t    par_cls  = va_arg(par, u16_t)   ;
            u32_t    par_ttl  = va_arg(par, u32_t)   ;
            u16_t    par_len  = va_arg(par, u16_t)   ;
            void*    par_data = va_arg(par, void*)   ;

            if (par_req->dns != par_res->dns)
                return false_t;

            u16_t req = ptr_dist(par_req->form.name, par_res->dns->ptr);
                  req = be16    (req | 0xC000)                         ;
            if (null(par_res->form.type     = ptr_wr16(par_res->form.name    , req)))      return false_t;
            if (null(par_res->form.cls      = ptr_wr16(par_res->form.type    , par_type))) return false_t;
            if (null(par_res->form.ttl      = ptr_wr16(par_res->form.cls     , par_cls)))  return false_t;
            if (null(par_res->form.data_len = ptr_wr32(par_res->form.ttl     , par_ttl)))  return false_t;
            if (null(par_res->form.data     = ptr_wr16(par_res->form.data_len, par_len)))  return false_t;
                        
            par_res->dns->ptr_off = ptr_write(par_res->form.data, par_data, par_len);
            return true_t;
}

bool_t 
    dns_res_init
        (dns_res* par_res, u32_t par_count, va_list par) {
            par_res->dns = va_arg(par, dns*);
            if (!par_res->dns)
                return false_t;

            par_res->ptr = par_res->dns->ptr_off;
            switch(par_count) {
            case 1: if (!dns_res_do_init_from(par_res))            goto init_failed;
                    break;
            case 7: if (!dns_res_do_init_from_param(par_res, par)) goto init_failed;
                    break;
            }

            return true_t;
    init_failed:
            del(par_res->dns);
            return    false_t;
}

bool_t 
    dns_res_init_as_clone
        (dns_res* par, dns_res* par_clone) {
            return false_t;
}

void
    dns_res_deinit
        (dns_res* par)  {
}

u64_t  
    dns_res_size()            {
        return sizeof(dns_res);
}