#ifndef __DETAILS_DNS_H__
#define __DETAILS_DNS_H__

#include "name.h"
#include "head.h"
#include "list.h"

#include "req.h"
#include "res.h"

extern obj_trait dns_t          ;
typedef struct   dns            {
    obj      head               ;
    ptr      ptr       , ptr_off;
    list     req       ,
             res       ,
             auth      ,
             additional;
    dns_head dns_head  ;
}   dns;

bool_t dns_init         (dns*, u32_t, va_list);
bool_t dns_init_as_clone(dns*, dns*)          ;
void   dns_deinit       (dns*)                ;
u64_t  dns_size         ()                    ;

#endif