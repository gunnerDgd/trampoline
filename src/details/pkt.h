#ifndef __DETAILS_PKT_H__
#define __DETAILS_PKT_H__

#include <list.h>
#include <box.h>

#include "head.h"

extern obj_trait pkt_t      ;
typedef struct   pkt        {
    obj   head              ;
    box  *box               ;
    u8_t *ptr     , *ptr_off;
    list  req     ,
          res     ,
          auth    ,
          add     ;
    head  dns_head;
}   pkt;

bool_t pkt_new  (pkt*, u32_t, va_list);
bool_t pkt_clone(pkt*, pkt*)          ;
void   pkt_del  (pkt*)                ;

#endif