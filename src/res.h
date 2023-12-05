#ifndef __DNS_RES_H__
#define __DNS_RES_H__

#include <obj.h>
#include <v4.h>

#include "req.h"
#include "soa.h"
#include "rec.h"

typedef void* dns_res;

dns_res dns_pkt_res            (dns_pkt);
dns_res dns_pkt_auth_res       (dns_pkt);

u64_t   dns_res_count          (dns_pkt);
dns_res dns_res_next           (dns_res);

str*    dns_res_req            (dns_res);
u16_t   dns_res_type           (dns_res);
u16_t   dns_res_cls            (dns_res);
u32_t   dns_res_ttl            (dns_res);

str*    dns_res_as_a           (dns_res);
str*    dns_res_as_cname       (dns_res);
str*    dns_res_as_ptr         (dns_res);
dns_soa dns_res_as_soa         (dns_res);

void    dns_res_rec            (dns_pkt, dns_req, dns_rec)           ;
dns_res dns_res_a              (dns_pkt, dns_req, u32_t, v4*)        ;
dns_res dns_res_a_str          (dns_pkt, dns_req, u32_t, str*)       ;
dns_res dns_res_a_cstr         (dns_pkt, dns_req, u32_t, const char*);

dns_res dns_res_cname          (dns_pkt, dns_req, u32_t, str*)       ;
dns_res dns_res_cname_cstr     (dns_pkt, dns_req, u32_t, const char*);

dns_res dns_res_ptr            (dns_pkt, dns_req, u32_t, str*)       ;
dns_res dns_res_ptr_cstr       (dns_pkt, dns_req, u32_t, const char*);
dns_res dns_res_soa            (dns_pkt, dns_req, u32_t, dns_soa)    ;

dns_res dns_auth_res_a         (dns_pkt, dns_req, u32_t, v4*)        ;
dns_res dns_auth_res_a_str     (dns_pkt, dns_req, u32_t, str*)       ;
dns_res dns_auth_res_a_cstr    (dns_pkt, dns_req, u32_t, const char*);

dns_res dns_auth_res_cname     (dns_pkt, dns_req, u32_t, str*)       ;
dns_res dns_auth_res_cname_cstr(dns_pkt, dns_req, u32_t, const char*);

dns_res dns_auth_res_ptr       (dns_pkt, dns_req, u32_t, str*)       ;
dns_res dns_auth_res_ptr_cstr  (dns_pkt, dns_req, u32_t, const char*);
dns_res dns_auth_res_soa       (dns_pkt, dns_req, u32_t, dns_soa)    ;

#endif