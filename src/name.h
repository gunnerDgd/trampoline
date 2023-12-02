#ifndef __DNS_NAME_H__
#define __DNS_NAME_H__

#include <obj.h>

typedef obj* dns_name;

dns_name    dns_name_new_from_cstr(const char*);
dns_name    dns_name_new          (str*)       ;
str*        dns_name_as_str       (dns_name)   ;

#endif