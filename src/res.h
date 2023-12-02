#ifndef __DNS_RES_H__
#define __DNS_RES_H__

#include <obj.h>
#include <v4.h>

#include "req.h"

typedef void* dns_res;

u64_t   dns_res_count   (obj*)   ;
dns_res dns_res_from    (obj*)   ;
dns_res dns_res_next    (dns_res);

str*    dns_res_req     (dns_res);
u16_t   dns_res_type    (dns_res);
u16_t   dns_res_cls     (dns_res);
u32_t   dns_res_ttl     (dns_res);

str*    dns_res_as_a    (dns_res);
str*    dns_res_as_cname(dns_res);

dns_res dns_res_a       (obj*, dns_req, u32_t, v4*) ;
dns_res dns_res_cname   (obj*, dns_req, u32_t, str*);

#endif