#ifndef __DNS_BUILD_CNAME_H__
#define __DNS_BUILD_CNAME_H__

#include "obj.h"

bool_t dns_build_req_cname     (obj*, str*              , u16_t);
bool_t dns_build_req_cname_cstr(obj*, const char*, u64_t, u16_t);

bool_t dns_build_res_cname     (obj*, obj*, u16_t, u32_t, str*)              ;
bool_t dns_build_res_cname_cstr(obj*, obj*, u16_t, u32_t, const char*, u64_t);

#endif