#ifndef __DNS_REQ_H__
#define __DNS_REQ_H__

#include "dns.h"

typedef void* dns_req;

u64_t   dns_req_count(obj*)      ;
dns_req dns_req_from (obj*)      ;
dns_req dns_req_next (dns_req)   ;

str*    dns_req_name (dns_req)   ;
u16_t   dns_req_type (dns_req)   ;
u16_t   dns_req_cls  (dns_req)   ;

dns_req dns_req_a    (obj*, str*);
dns_req dns_req_cname(obj*, str*);

#endif