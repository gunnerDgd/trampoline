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

extern obj_trait __dns_res_trait;
typedef struct   __dns_res      {
    obj            head;
    struct __dns  *dns ;
    ptr            ptr ;
    __dns_res_form form;
}   __dns_res          ;

bool_t __dns_res_from         (__dns_res*);
bool_t __dns_res_from_param   (__dns_res*, struct __dns_req*, u16_t, u16_t, u32_t, u16_t, void*);

bool_t __dns_res_init         (__dns_res*, u32_t, va_list);
bool_t __dns_res_init_as_clone(__dns_res*, __dns_res*)    ;
void   __dns_res_deinit       (__dns_res*)                ;
u64_t  __dns_res_size         ()                          ;

#endif