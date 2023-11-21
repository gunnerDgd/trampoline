#ifndef __DNS_NAME_H__
#define __DNS_NAME_H__

#include "obj.h"

obj* dns_name_from_str (str*)			   ;
obj* dns_name_from_cstr(const char*, u64_t);
str* dns_name_to_str   (obj*)			   ;

#endif