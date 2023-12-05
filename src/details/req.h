#ifndef __DETAILS_DNS_REQ_H__
#define __DETAILS_DNS_REQ_H__

#include "name.h"

typedef struct req_form {
    u8_t  *name;
    u16_t *type,
          *cls ;
}   req_form   ;

extern obj_trait req_t;
typedef struct   req  {
    obj          head;
    struct pkt  *pkt ;
    req_form     form;
}   req;

bool_t req_new         (req*, u32_t, va_list)     ;
bool_t req_new_from    (req*)                     ;
bool_t req_new_from_par(req*, name*, u16_t, u16_t);
bool_t req_clone       (req*, req*)               ;
void   req_del         (req*)                     ;

name*  req_name        (req*);
u16_t  req_type        (req*);
u16_t  req_cls         (req*);

#endif