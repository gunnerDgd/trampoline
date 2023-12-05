#include "pkt.h"
#include "endian.h"

#include "req.h"
#include "res.h"

obj_trait pkt_t         = {
    .on_new   = &pkt_new  ,
    .on_clone = &pkt_clone,
    .on_ref   =          0,
    .on_del   = &pkt_del  ,
    .size     = sizeof(pkt)
};

bool_t 
    pkt_new
        (pkt* par_dns, u32_t par_count, va_list par) {
            par_dns->box     = va_arg(par, box*)     ; if(!par_dns->box) return false_t;
            par_dns->ptr     = box_ptr(par_dns->box) ;
            par_dns->ptr_off = box_ptr(par_dns->box) ;

            if(!make_at(&par_dns->req , list_t) from(0)) goto new_failed;
            if(!make_at(&par_dns->res , list_t) from(0)) goto new_failed;
            if(!make_at(&par_dns->auth, list_t) from(0)) goto new_failed;
            if(!make_at(&par_dns->add , list_t) from(0)) goto new_failed;

            if (par_count == 1)                                           {
                if (!make_at(&par_dns->dns_head, &head_t) from(1, par_dns))
                    goto new_failed;

                u16_t idx_req  = be16(par_dns->dns_head.form->req); if (!idx_req) goto new_failed;
                u16_t idx_res  = be16(par_dns->dns_head.form->res);

                while (idx_req--)                            {
                    req *req = make(&req_t) from (1, par_dns);
                    if (!req)                                goto new_failed;
                    if (!list_push_back(&par_dns->req, req)) goto new_failed;
                    del(req);
                }

                while (idx_res--)                            {
                    res *res = make(&res_t) from (1, par_dns);
                    if (!res)                                goto new_failed;
                    if (!list_push_back(&par_dns->res, res)) goto new_failed;
                    del(res);
                }

                ref(par_dns->box);
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

            if  (!ret) goto new_failed;
            ref (par_dns->box);
            return true_t;
    new_failed:
            del(&par_dns->req) ;
            del(&par_dns->res) ;
            del(&par_dns->auth);
            del(&par_dns->add) ;
            return false_t;
}

bool_t 
    pkt_clone
        (pkt* par, pkt* par_clone) {
            return false_t;
}

void   
    pkt_del
        (pkt* par)             {
            del(&par->req)     ;
            del(&par->res)     ;
            del(&par->auth)    ;
            del(&par->add)     ;
            del(&par->dns_head);
            del(par->box)      ;
}
