#ifndef __DNS_BUILD_H__
#define __DNS_BUILD_H__

#include "obj.h"
#include "dns.h"

#include "v4.h"

extern obj_trait* dns_builder_t;
typedef struct    dns_builder { u8_t dns_builder[64]; } dns_builder;

bool_t dns_build_head     (dns_builder*, u16_t, u16_t);
bool_t dns_build_req_a    (dns_builder*, str* , u16_t);
bool_t dns_build_req_aaaa (dns_builder*, str* , u16_t);
bool_t dns_build_req_cname(dns_builder*, str* , u16_t);

bool_t dns_build_res_a    (dns_builder*, str* , u16_t, u16_t, u16_t, v4*) ;
bool_t dns_build_res_cname(dns_builder*, str* , u16_t, u16_t, u16_t, str*);
dns*   dns_build          (dns_builder*)                                  ;

#endif