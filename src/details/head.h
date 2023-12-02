#ifndef __DETAILS_DNS_HEAD_H__
#define __DETAILS_DNS_HEAD_H__

#include "obj.h"
#include "box.h"

typedef struct head_form {
    u16_t id        ,
          flag      ,
          req       ,
          res       , 
          auth      ,
          additional;
}   head_form       ;

extern obj_trait head_t;
typedef struct   head  {
    obj          head;
    struct dns  *dns ;
    head_form   *form;
}   head;

bool_t head_new       (head*, u32_t, va_list);
bool_t head_clone     (head*, head*)         ;
void   head_del       (head*)                ;

u16_t  head_id        (head*);
u16_t  head_flag      (head*);
u16_t  head_req       (head*);
u16_t  head_res       (head*);
u16_t  head_auth      (head*);
u16_t  head_additional(head*);

#endif