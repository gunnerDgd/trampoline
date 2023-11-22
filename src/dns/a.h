#ifndef __DNS_DNS_A_H__
#define __DNS_DNS_A_H__

#include "v4.h"

obj* dns_req_a     (obj*, obj*              , u16_t);
obj* dns_req_a_str (obj*, str*              , u16_t);
obj* dns_req_a_cstr(obj*, const char*, u64_t, u16_t);

obj* dns_res_a     (obj*, obj*, u16_t, u32_t, v4*)        ;
obj* dns_res_a_cstr(obj*, obj*, u16_t, u32_t, const char*);

#endif