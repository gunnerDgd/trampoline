#ifndef __DETAILS_DNS_HEAD_H__
#define __DETAILS_DNS_HEAD_H__

#include "obj.h"
#include "box.h"

typedef struct __dns_head_form {
    u16_t id        ,
          opcode    ,
          req       ,
          res       , 
          auth      ,
          additional;
}   __dns_head_form ;

extern obj_trait __dns_head_trait;
typedef struct   __dns_head      {
    obj              head;
    struct __dns    *dns ;
    ptr              ptr ;
    __dns_head_form *form;
}   __dns_head;

bool_t __dns_head_init         (__dns_head*, u32_t, va_list);
bool_t __dns_head_init_as_clone(__dns_head*, __dns_head*)   ;
void   __dns_head_deinit       (__dns_head*)                ;
u64_t  __dns_head_size         ()                           ;

u16_t __dns_head_id        (__dns_head*);
u16_t __dns_head_opcode    (__dns_head*);
u16_t __dns_head_req       (__dns_head*);
u16_t __dns_head_res       (__dns_head*);
u16_t __dns_head_auth      (__dns_head*);
u16_t __dns_head_additional(__dns_head*);

#endif