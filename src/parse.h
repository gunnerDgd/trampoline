#ifndef __DNS_PARSER_H__
#define __DNS_PARSER_H__

#include "obj.h"

obj* dns_parse_from(ptr)                     ;
void dns_parse_req (obj*, u16_t, u16_t)      ;
void dns_parse_res (obj*, u16_t, u16_t, str*);
obj* dns_parse     (obj*)                    ;

#endif