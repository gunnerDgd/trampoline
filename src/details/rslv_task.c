#include "rslv_task.h"
#include "rslv.h"

#include <stdio.h>

obj_trait rslv_task_t         = {
    .on_new   = &rslv_task_new  ,
    .on_clone = &rslv_task_clone,
    .on_ref   = 0               ,
    .on_del   = &rslv_task_del  ,
    .size     = sizeof(rslv_task)
};

void* 
    rslv_task_main
        (rslv_task* par)          {
            str    *req_name      ;
            dns_req req = par->req;
            for ( ; req ; req = dns_req_next(req)) {
                dns_rec rec = dns_ns_find(par->rslv->ns, (req_name = dns_req_name(req)));
                if (!rec)         {
                    del (req_name);
                    par->req = req;
                    return par;
                }

                dns_res_rec(par->pkt, req, rec);
                del(req_name);
            }

            u8_t*  pkt      = dns_pkt_ptr (par->pkt); if (!pkt)          goto main_failed;
            u64_t  pkt_size = dns_pkt_size(par->pkt); if (pkt_size < 12) goto main_failed;
  
            await(udp_send_to(par->cli, pkt, pkt_size, par->addr));
            del(par);
            return 0;
    main_failed:
            del (par);
            return 0 ;
}

bool_t  
    rslv_task_new
        (rslv_task* par_task, u32_t par_count, va_list par) {
            par_task->rslv = va_arg(par, rslv*)        ;
            par_task->pkt  = va_arg(par, dns_pkt)      ;
            par_task->cli  = va_arg(par, udp*)         ;
            par_task->addr = va_arg(par, v4*)          ;
            par_task->req  = dns_pkt_req(par_task->pkt);

            return true_t;
}

bool_t
    rslv_task_clone
        (rslv_task* par, rslv_task* par_clone) {
            return false_t;
}

void
    rslv_task_del
        (rslv_task* par)  {
            del(par->pkt) ;
            del(par->cli) ;
            del(par->addr);
            del(par->rslv);
}

str*    rslv_req_name(rslv_task* par) { return dns_req_name(par->req); }
u16_t   rslv_req_type(rslv_task* par) { return dns_req_type(par->req); }
u16_t   rslv_req_cls (rslv_task* par) { return dns_req_cls (par->req); }
dns_req rslv_req_next(rslv_task* par) { return (par->req = dns_req_next(par->req)); }
task    rslv_res     (rslv_task* par) { return async(rslv_task_main, par); }

void    
    rslv_rec
        (rslv_task* par, dns_rec par_rec) {
            return dns_res_rec (
                par->pkt, 
                par->req, 
                par_rec
            );
}


dns_res 
    rslv_a
        (rslv_task* par, u32_t par_ttl, v4* par_res) { 
            return dns_res_a (
                par->pkt, 
                par->req , 
                par_ttl , 
                par_res
            ); 
}

dns_res 
    rslv_a_str
        (rslv_task* par, u32_t par_ttl, str* par_res) { 
            return dns_res_a_str (
                par->pkt, 
                par->req , 
                par_ttl , 
                par_res
            ); 
}

dns_res 
    rslv_a_cstr
        (rslv_task* par, u32_t par_ttl, const char* par_res) { 
            return dns_res_a_cstr (
                par->pkt, 
                par->req , 
                par_ttl , 
                par_res
            );
}

dns_res 
    rslv_cname
        (rslv_task* par, u32_t par_ttl, str* par_res) {
            return dns_res_cname (
                par->pkt,
                par->req ,
                par_ttl ,
                par_res
            );
}

dns_res 
    rslv_cname_cstr
        (rslv_task* par, u32_t par_ttl, const char* par_res) {
            return dns_res_cname_cstr (
                par->pkt,
                par->req ,
                par_ttl ,
                par_res
            );
}

dns_res 
    rslv_soa
        (rslv_task* par, u32_t par_ttl, dns_soa par_soa) {
            return dns_res_soa (
                par->pkt,
                par->req ,
                par_ttl ,
                par_soa
            );
}

dns_res 
    rslv_ptr
        (rslv_task* par, u32_t par_ttl, str* par_ptr) {
            return dns_res_ptr (
                par->pkt,
                par->req ,
                par_ttl ,
                par_ptr
            );
}

dns_res 
    rslv_ptr_cstr
        (rslv_task* par, u32_t par_ttl, const char* par_ptr) {
            return dns_res_ptr_cstr (
                par->pkt,
                par->req ,
                par_ttl ,
                par_ptr
            );
}

dns_res 
    rslv_auth_a
        (rslv_task* par, u32_t par_ttl, v4* par_res) { 
            return dns_auth_res_a (
                par->pkt, 
                par->req , 
                par_ttl , 
                par_res
            ); 
}

dns_res 
    rslv_auth_a_str
        (rslv_task* par, u32_t par_ttl, str* par_res) { 
            return dns_auth_res_a_str (
                par->pkt, 
                par->req , 
                par_ttl , 
                par_res
            ); 
}

dns_res 
    rslv_auth_a_cstr
        (rslv_task* par, u32_t par_ttl, const char* par_res) { 
            return dns_auth_res_a_cstr (
                par->pkt, 
                par->req , 
                par_ttl , 
                par_res
            );
}

dns_res 
    rslv_auth_cname
        (rslv_task* par, u32_t par_ttl, str* par_res) {
            return dns_auth_res_cname (
                par->pkt,
                par->req ,
                par_ttl ,
                par_res
            );
}

dns_res 
    rslv_auth_cname_cstr
        (rslv_task* par, u32_t par_ttl, const char* par_res) {
            return dns_auth_res_cname_cstr (
                par->pkt,
                par->req ,
                par_ttl ,
                par_res
            );
}

dns_res 
    rslv_auth_soa
        (rslv_task* par, u32_t par_ttl, dns_soa par_soa) {
            return dns_auth_res_soa (
                par->pkt,
                par->req ,
                par_ttl ,
                par_soa
            );
}

dns_res 
    rslv_auth_ptr
        (rslv_task* par, u32_t par_ttl, str* par_ptr) {
            return dns_auth_res_ptr (
                par->pkt,
                par->req ,
                par_ttl ,
                par_ptr
            );
}

dns_res 
    rslv_auth_ptr_cstr
        (rslv_task* par, u32_t par_ttl, const char* par_ptr) {
            return dns_auth_res_ptr_cstr (
                par->pkt,
                par->req ,
                par_ttl ,
                par_ptr
            );
}