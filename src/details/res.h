#ifndef __DETAILS_DNS_RES_H__
#define __DETAILS_DNS_RES_H__

#include "name.h"

typedef struct dns_res_form {
    ptr name      ,
        type      ,
        cls       ,
        ttl       ,
        data_len  ,
        data      ;
}   dns_res_form  ;

extern obj_trait dns_res_t;
typedef struct   dns_res  {
    obj          head;
    struct dns  *dns ;
    ptr          ptr ;
    dns_res_form form;
}   dns_res          ;

bool_t dns_res_do_init_from      (dns_res*)                ;
bool_t dns_res_do_init_from_param(dns_res*, va_list)       ;
bool_t dns_res_init              (dns_res*, u32_t, va_list);
bool_t dns_res_init_as_clone     (dns_res*, dns_res*)      ;
void   dns_res_deinit            (dns_res*)                ;
u64_t  dns_res_size              ()                        ;

#endif