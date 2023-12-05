#ifndef __DNS_REQ_H__
#define __DNS_REQ_H__

#include "pkt.h"
#include <v4.h>

typedef void* dns_req;

dns_req dns_pkt_req       (dns_pkt)             ;
u64_t   dns_req_count     (dns_pkt)             ;
dns_req dns_req_next      (dns_req)             ;

str*    dns_req_name      (dns_req)             ;
u16_t   dns_req_type      (dns_req)             ;
u16_t   dns_req_cls       (dns_req)             ;

dns_req dns_req_a         (dns_pkt, str*)       ;
dns_req dns_req_a_cstr    (dns_pkt, const char*);

dns_req dns_req_cname     (dns_pkt, str*)       ;
dns_req dns_req_cname_cstr(dns_pkt, const char*);

dns_req dns_req_ptr       (dns_pkt, v4*)        ;
dns_req dns_req_ptr_str   (dns_pkt, str*)       ;
dns_req dns_req_ptr_cstr  (dns_pkt, const char*);

dns_req dns_req_soa       (dns_pkt, str*)       ;
dns_req dns_req_soa_cstr  (dns_pkt, const char*);

#endif