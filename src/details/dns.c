#include "dns.h"
#include "endian.h"

#include "req.h"
#include "res.h"

obj_trait dns_trait     = {
    .on_new   = &dns_new  ,
    .on_clone = &dns_clone,
    .on_ref   =          0,
    .on_del   = &dns_del  ,
    .size     = sizeof(dns)
};

bool_t 
    dns_new
        (dns* par_dns, u32_t par_count, va_list par) {
            par_dns->box     = va_arg(par, box*)     ; if(!par_dns->box) return false_t;
            par_dns->ptr     = box_ptr(par_dns->box) ;
            par_dns->ptr_off = box_ptr(par_dns->box) ;

            if(!make_at(&par_dns->req       , list_t) from(0)) goto dns_init_failed;
            if(!make_at(&par_dns->res       , list_t) from(0)) goto dns_init_failed;
            if(!make_at(&par_dns->auth      , list_t) from(0)) goto dns_init_failed;
            if(!make_at(&par_dns->additional, list_t) from(0)) goto dns_init_failed;

            if (par_count == 1)                                           {
                if (!make_at(&par_dns->dns_head, &head_t) from(1, par_dns))
                    goto dns_init_failed;

                u16_t idx_req = be16(par_dns->dns_head.form->req); if (!idx_req) goto dns_init_failed;
                u16_t idx_res = be16(par_dns->dns_head.form->res);

                while (idx_req--) if(!list_push_back(&par_dns->req, make(&req_t) from(1, par_dns))) goto dns_init_failed;
                while (idx_res--) if(!list_push_back(&par_dns->res, make(&res_t) from(1, par_dns))) goto dns_init_failed;

                return true_t;
            }
            u16_t  par_id   = va_arg  (par, u16_t);
            u16_t  par_flag = va_arg  (par, u16_t);
            bool_t ret      = make_at (&par_dns->dns_head, &head_t) from (
                3       ,
                par_dns ,
                par_id  ,
                par_flag
            );

            if  (!ret) goto dns_init_failed;
            return true_t;
    dns_init_failed:
            del(&par_dns->req)       ;
            del(&par_dns->res)       ;
            del(&par_dns->auth)      ;
            del(&par_dns->additional);
            return false_t;
}

bool_t 
    dns_clone
        (dns* par, dns* par_clone) {
            return false_t;
}

void   
    dns_del
        (dns* par)               {
            del(&par->req)       ;
            del(&par->res)       ;
            del(&par->auth)      ;
            del(&par->additional);
            del(&par->dns_head)  ;
}
