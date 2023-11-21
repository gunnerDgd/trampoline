#ifndef __DETAILS_DNS_RES_H__
#define __DETAILS_DNS_RES_H__

#include "name.h"

typedef struct __dns_res_form {
    ptr name      ,
        type      ,
        cls       ,
        ttl       ,
        data_len  ,
        data      ;
}   __dns_res_form;

typedef union __dns_res_data {
    u32_t      a      ;
    u64_t      aaaa[2];
    __dns_name cname  ;
}   __dns_res_data    ;

extern obj_trait __dns_res_trait;
typedef struct   __dns_res      {
    obj            head     ;
    struct __dns  *dns      ;
    ptr            ptr      ;
    __dns_res_form form     ;
    __dns_name     req      ;
    u16_t          data_type;
    __dns_res_data data     ;
}   __dns_res               ;

bool_t __dns_res_init         (__dns_res*, u32_t, va_list);
bool_t __dns_res_init_as_clone(__dns_res*, __dns_res*)    ;
void   __dns_res_deinit       (__dns_res*)                ;
u64_t  __dns_res_size         ()                          ;
str*   __dns_res_name         (__dns_res*);
u64_t  __dns_res_name_len     (__dns_res*);

#endif