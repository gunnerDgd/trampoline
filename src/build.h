#ifndef __DNS_BUILD_H__
#define __DNS_BUILD_H__

#include "obj.h"
#include "dns.h"

#include "v4.h"

obj*   dns_build_from         (ptr) ;
obj*   dns_build_from_existing(obj*);

bool_t dns_build_head         (obj*, u16_t, u16_t);
obj*   dns_build              (obj*)              ;

#endif