#ifndef __DETAILS_DNS_HEAD_H__
#define __DETAILS_DNS_HEAD_H__

#include "obj.h"
#include "box.h"

typedef struct dns_head_form {
    u16_t id        ,
          flag      ,
          req       ,
          res       , 
          auth      ,
          additional;
}   dns_head_form   ;

extern obj_trait dns_head_t;
typedef struct   dns_head  {
    obj            head;
    struct dns    *dns ;
    ptr            ptr ;
    dns_head_form *form;
}   dns_head;

bool_t dns_head_init         (dns_head*, u32_t, va_list);
bool_t dns_head_init_as_clone(dns_head*, dns_head*)     ;
void   dns_head_deinit       (dns_head*)                ;
u64_t  dns_head_size         ()                         ;

#endif