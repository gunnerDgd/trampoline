#ifndef __DETAILS_DNS_NAME_H__
#define __DETAILS_DNS_NAME_H__

#include "obj.h"
#include "box.h"
#include "str.h"

extern obj_trait __dns_name_trait;
typedef struct   __dns_name      {
    obj           head    ;
    str           name    ;
    ptr           name_ptr;
    u64_t         len     ;
    struct __dns* dns     ;
}   __dns_name;

bool_t __dns_name_init         (__dns_name*, u32_t, va_list);
bool_t __dns_name_init_as_clone(__dns_name*, __dns_name*)   ;
void   __dns_name_deinit       (__dns_name*)                ;
u64_t  __dns_name_size         ()                           ;
str*   __dns_name_str          (__dns_name*)                ;
u64_t  __dns_name_len          (__dns_name*)                ;

#endif