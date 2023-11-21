#ifndef __DETAILS_DNS_H__
#define __DETAILS_DNS_H__

#include "name.h"
#include "head.h"
#include "list.h"

#include "req.h"
#include "res.h"

extern obj_trait __dns_trait      ;
typedef struct   __dns            {
    obj        head               ;
    ptr        ptr       , ptr_off;
    list       req       ,
               res       ,
               auth      ,
               additional;
    __dns_head dns_head  ;
}   __dns;

bool_t __dns_init         (__dns*, u32_t, va_list);
bool_t __dns_init_as_clone(__dns*, __dns*)        ;
void   __dns_deinit       (__dns*)                ;
u64_t  __dns_size         ()                      ;

#endif