#ifndef __DETAILS_DNS_PARSE_H__
#define __DETAILS_DNS_PARSE_H__

#include "dns.h"

extern obj_trait __dns_parser_trait;
typedef struct   __dns_parser      {
    obj         head    ;
    __dns      *dns     ;
    u16_t       req_type,
                req_cls ,

                res_type,
                res_cls ;
    __dns_name* res_req ;
}   __dns_parser;

bool_t __dns_parser_init         (__dns_parser*, u32_t, va_list);
bool_t __dns_parser_init_as_clone(__dns_parser*, __dns_parser*) ;
void   __dns_parser_deinit       (__dns_parser*)                ;
u64_t  __dns_parser_size         ()                             ;

bool_t __dns_do_parse_head       (__dns_parser*);
bool_t __dns_do_parse_req        (__dns_parser*);
bool_t __dns_do_parse_res        (__dns_parser*);

void   __dns_parse_req           (__dns_parser*, u16_t, u16_t)             ;
void   __dns_parse_res           (__dns_parser*, u16_t, u16_t, __dns_name*);
__dns* __dns_parse               (__dns_parser*)                           ;

#endif