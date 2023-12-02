#ifndef __DETAILS_PKT_H__
#define __DETAILS_PKT_H__

#include <list.h>
#include <box.h>

#include "head.h"

extern obj_trait dns_trait    ;
typedef struct   dns          {
    obj   head                ;
    box  *box                 ;
    u8_t *ptr       , *ptr_off;
    list  req       ,
          res       ,
          auth      ,
          additional;
    head  dns_head  ;
}   dns;

bool_t dns_new  (dns*, u32_t, va_list);
bool_t dns_clone(dns*, dns*)          ;
void   dns_del  (dns*)                ;

#endif