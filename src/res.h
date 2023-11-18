#ifndef __DNS_RES_H__
#define __DNS_RES_H__

#include "obj.h"

u16_t dns_res_type(obj*);
u16_t dns_res_cls (obj*);
u16_t dns_res_ttl (obj*);
u16_t dns_res_len (obj*);

bool_t dns_res_as_a    (obj*, str*);
bool_t dns_res_as_aaaa (obj*, str*);
bool_t dns_res_as_cname(obj*, str*);

#endif