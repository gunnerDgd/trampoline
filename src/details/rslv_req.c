#include "rslv_req.h"
#include "rslv.h"

#include "pkt.h"

obj_trait rslv_req_t         = {
    .on_new   = &rslv_req_new  ,
    .on_clone = &rslv_req_clone,
    .on_ref   = 0              ,
    .on_del   = &rslv_req_del  ,
    .size     = sizeof(rslv_req)
};

u64_t
    rslv_res_run
        (rslv_req* par)        {
            pkt* pkt = par->pkt;
            pkt->dns_head.form->flag |= 0x0080;

            u8_t*  ptr      = dns_pkt_ptr (par->pkt); if (!ptr)      goto run_failed;
            u64_t  ptr_size = dns_pkt_size(par->pkt); if (!ptr_size) goto run_failed;
            u64_t  ret      = await(udp_send_to(par->cli, ptr, ptr_size, par->addr)); del(par);
            return ret;
    run_failed:
            del(par);
            return 0;
}

bool_t  
    rslv_req_new
        (rslv_req* par_task, u32_t par_count, va_list par) {
            par_task->rslv = va_arg(par, rslv*)  ;
            par_task->pkt  = va_arg(par, dns_pkt);
            par_task->cli  = va_arg(par, udp*)   ;
            par_task->addr = va_arg(par, v4*)    ;
            par_task->req  = 0                   ;

            return true_t;
}

bool_t
    rslv_req_clone
        (rslv_req* par, rslv_req* par_clone) {
            return false_t;
}

void
    rslv_req_del
        (rslv_req* par)   {
            del(par->pkt) ;
            del(par->cli) ;
            del(par->addr);
            del(par->rslv);
}

str*    
    rslv_req_name
        (rslv_req* par)                  { 
            return dns_req_name(par->req); 
}

u16_t
    rslv_req_type
        (rslv_req* par)                  { 
            return dns_req_type(par->req); 
}

u16_t
    rslv_req_cls 
        (rslv_req* par)                  { 
            return dns_req_cls (par->req); 
}

task    
    rslv_res
        (rslv_req* par)                    { 
            return async(rslv_res_run, par);
}

bool_t
    rslv_next
        (rslv_req* par)                         { 
            if(!par->req)                       {
                par->req = dns_pkt_req(par->pkt);
                return par->req != 0;
            }

            par->req = dns_req_next(par->req);
            return par->req;
}

dns_res 
    rslv_a
        (rslv_req* par, u32_t par_ttl, v4* par_res) { 
            return dns_res_a (
                par->pkt, 
                par->req , 
                par_ttl , 
                par_res
            ); 
}

dns_res 
    rslv_a_str
        (rslv_req* par, u32_t par_ttl, str* par_res) { 
            return dns_res_a_str (
                par->pkt, 
                par->req , 
                par_ttl , 
                par_res
            ); 
}

dns_res 
    rslv_a_cstr
        (rslv_req* par, u32_t par_ttl, const char* par_res) { 
            return dns_res_a_cstr (
                par->pkt, 
                par->req , 
                par_ttl , 
                par_res
            );
}

dns_res 
    rslv_cname
        (rslv_req* par, u32_t par_ttl, str* par_res) {
            return dns_res_cname (
                par->pkt,
                par->req ,
                par_ttl ,
                par_res
            );
}

dns_res 
    rslv_cname_cstr
        (rslv_req* par, u32_t par_ttl, const char* par_res) {
            return dns_res_cname_cstr (
                par->pkt,
                par->req ,
                par_ttl ,
                par_res
            );
}

dns_res 
    rslv_soa
        (rslv_req* par, u32_t par_ttl, dns_soa par_soa) {
            return dns_res_soa (
                par->pkt,
                par->req ,
                par_ttl ,
                par_soa
            );
}

dns_res 
    rslv_ptr
        (rslv_req* par, u32_t par_ttl, str* par_ptr) {
            return dns_res_ptr (
                par->pkt,
                par->req ,
                par_ttl ,
                par_ptr
            );
}

dns_res 
    rslv_ptr_cstr
        (rslv_req* par, u32_t par_ttl, const char* par_ptr) {
            return dns_res_ptr_cstr (
                par->pkt,
                par->req ,
                par_ttl ,
                par_ptr
            );
}

dns_res 
    rslv_auth_a
        (rslv_req* par, u32_t par_ttl, v4* par_res) { 
            return dns_auth_res_a (
                par->pkt, 
                par->req , 
                par_ttl , 
                par_res
            ); 
}

dns_res 
    rslv_auth_a_str
        (rslv_req* par, u32_t par_ttl, str* par_res) { 
            return dns_auth_res_a_str (
                par->pkt, 
                par->req , 
                par_ttl , 
                par_res
            ); 
}

dns_res 
    rslv_auth_a_cstr
        (rslv_req* par, u32_t par_ttl, const char* par_res) { 
            return dns_auth_res_a_cstr (
                par->pkt, 
                par->req , 
                par_ttl , 
                par_res
            );
}

dns_res 
    rslv_auth_cname
        (rslv_req* par, u32_t par_ttl, str* par_res) {
            return dns_auth_res_cname (
                par->pkt,
                par->req ,
                par_ttl ,
                par_res
            );
}

dns_res 
    rslv_auth_cname_cstr
        (rslv_req* par, u32_t par_ttl, const char* par_res) {
            return dns_auth_res_cname_cstr (
                par->pkt,
                par->req ,
                par_ttl ,
                par_res
            );
}

dns_res 
    rslv_auth_soa
        (rslv_req* par, u32_t par_ttl, dns_soa par_soa) {
            return dns_auth_res_soa (
                par->pkt,
                par->req ,
                par_ttl ,
                par_soa
            );
}

dns_res 
    rslv_auth_ptr
        (rslv_req* par, u32_t par_ttl, str* par_ptr) {
            return dns_auth_res_ptr (
                par->pkt,
                par->req ,
                par_ttl ,
                par_ptr
            );
}

dns_res 
    rslv_auth_ptr_cstr
        (rslv_req* par, u32_t par_ttl, const char* par_ptr) {
            return dns_auth_res_ptr_cstr (
                par->pkt,
                par->req ,
                par_ttl ,
                par_ptr
            );
}