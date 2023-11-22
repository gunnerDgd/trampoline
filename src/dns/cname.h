#ifndef __DNS_DNS_CNAME_H__
#define __DNS_DNS_CNAME_H__

#include "obj.h"

obj* dns_req_cname     (obj*, obj*              , u16_t);
obj* dns_req_cname_str (obj*, str*              , u16_t);
obj* dns_req_cname_cstr(obj*, const char*, u64_t, u16_t);

obj* dns_res_cname     (obj*, obj*, u16_t, u32_t, obj*)              ;
obj* dns_res_cname_str (obj*, obj*, u16_t, u32_t, str*)              ;
obj* dns_res_cname_cstr(obj*, obj*, u16_t, u32_t, const char*, u64_t);

#endif