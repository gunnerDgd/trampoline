#ifndef __DNS_NAME_H__
#define __DNS_NAME_H__

#include "obj.h"

obj* dns_name_new     (str*)              ;
obj* dns_name_new_cstr(const char*, u64_t);
str* dns_name_as_str  (obj*)			  ;

#endif