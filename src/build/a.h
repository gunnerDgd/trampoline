#ifndef __DNS_BUILD_A_H__
#define __DNS_BUILD_A_H__

#include "obj.h"

bool_t dns_build_req_a     (obj*, str*              , u16_t);
bool_t dns_build_req_a_cstr(obj*, const char*, u64_t, u16_t);

bool_t dns_build_res_a     (obj*, str*              , u16_t, u32_t, v4*);
bool_t dns_build_res_a_cstr(obj*, const char*, u64_t, u16_t, u32_t, v4*);

#endif