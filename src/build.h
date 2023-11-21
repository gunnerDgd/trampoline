#ifndef __DNS_BUILD_H__
#define __DNS_BUILD_H__

#include "obj.h"
#include "dns.h"

#include "v4.h"

obj*   dns_build_from         (ptr) ;
obj*   dns_build_from_existing(obj*);

bool_t dns_build_head         (obj*, u16_t, u16_t);
bool_t dns_build_req_a        (obj*, str* , u16_t);
bool_t dns_build_req_cname    (obj*, str* , u16_t);

bool_t dns_build_res_a        (obj*, str*, u16_t, u32_t, v4*) ;
bool_t dns_build_res_cname    (obj*, str*, u16_t, u32_t, str*);
obj*   dns_build              (obj*)                          ;

#endif