#ifndef __DETAILS_RSLV_REQ_H__
#define __DETAILS_RSLV_REQ_H__

#include <obj.h>
#include <udp.h>
#include <async.h>
#include <v4.h>

#include "../pkt.h"
#include "../req.h"
#include "../res.h"
#include "../rec.h"

extern obj_trait rslv_req_t;
typedef struct   rslv_req  {
    obj          head;
    struct rslv *rslv;
    dns_req      req ;
    dns_pkt      pkt ;
    udp         *cli ;
    v4          *addr;
}   rslv_req;

bool_t    rslv_req_new        (rslv_req*, u32_t, va_list)    ;
bool_t    rslv_req_clone      (rslv_req*, rslv_req*)         ;
void      rslv_req_del        (rslv_req*)                    ;

u64_t     rslv_res_run        (rslv_req*);
task      rslv_res            (rslv_req*)                    ;
str*      rslv_req_name       (rslv_req*)                    ;
u16_t     rslv_req_type       (rslv_req*)                    ;
u16_t     rslv_req_cls        (rslv_req*)                    ;
bool_t    rslv_next           (rslv_req*)                    ;

dns_res   rslv_a              (rslv_req*, u32_t, v4*)        ;
dns_res   rslv_a_str          (rslv_req*, u32_t, str*)       ;
dns_res   rslv_a_cstr         (rslv_req*, u32_t, const char*);

dns_res   rslv_cname          (rslv_req*, u32_t, str*)       ;
dns_res   rslv_cname_cstr     (rslv_req*, u32_t, const char*);

dns_res   rslv_soa            (rslv_req*, u32_t, dns_soa)    ;
dns_res   rslv_ptr            (rslv_req*, u32_t, str*)       ;
dns_res   rslv_ptr_cstr       (rslv_req*, u32_t, const char*);

dns_res   rslv_auth_a         (rslv_req*, u32_t, v4*)        ;
dns_res   rslv_auth_a_str     (rslv_req*, u32_t, str*)       ;
dns_res   rslv_auth_a_cstr    (rslv_req*, u32_t, const char*);

dns_res   rslv_auth_cname     (rslv_req*, u32_t, str*)       ;
dns_res   rslv_auth_cname_cstr(rslv_req*, u32_t, const char*);

dns_res   rslv_auth_soa       (rslv_req*, u32_t, dns_soa)    ;
dns_res   rslv_auth_ptr       (rslv_req*, u32_t, str*)       ;
dns_res   rslv_auth_ptr_cstr  (rslv_req*, u32_t, const char*);

#endif