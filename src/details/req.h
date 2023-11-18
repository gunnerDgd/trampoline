#ifndef __DETAILS_DNS_REQ_H__
#define __DETAILS_DNS_REQ_H__

#include "name.h"

typedef struct __dns_req_form {
    ptr name,
        type,
        cls ;
}   __dns_req_form   ; 

extern obj_trait __dns_req_trait;
typedef struct   __dns_req      {
    obj            head;
    struct __dns  *dns ;
    ptr            ptr ;
    __dns_name     name;
    __dns_req_form form;
}   __dns_req;

bool_t __dns_req_init         (__dns_req*, u32_t, va_list);
bool_t __dns_req_init_as_clone(__dns_req*, __dns_req*)    ;
void   __dns_req_deinit       (__dns_req*)                ;
u64_t  __dns_req_size         (__dns_req*)                ;

str*   __dns_req_name         (__dns_req*);
u16_t  __dns_req_type         (__dns_req*);
u16_t  __dns_req_cls          (__dns_req*);
u64_t  __dns_req_len          (__dns_req*);

#endif