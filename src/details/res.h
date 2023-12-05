#ifndef __DETAILS_DNS_RES_H__
#define __DETAILS_DNS_RES_H__

#include "name.h"

typedef struct res_form {
    u8_t  *name    ;
    u16_t *type    ,
          *cls     ;
    u32_t *ttl     ;
    u16_t *data_len;
    u8_t  *data    ;
}   res_form       ;

extern obj_trait res_t;
typedef struct   res  {
    obj          head;
    struct pkt  *pkt ;
    res_form     form;
}   res;

bool_t res_new_from    (res*)                                   ;
bool_t res_new_from_par(res*, u16_t, u16_t, u32_t, u16_t, u8_t*);
bool_t res_new         (res*, u32_t, va_list)                   ;
bool_t res_clone       (res*, res*)                             ;
void   res_del         (res*)                                   ;

name*  res_req         (res*);
u16_t  res_type        (res*);
u16_t  res_cls         (res*);
u32_t  res_ttl         (res*);
u16_t  res_data_len    (res*);


#endif