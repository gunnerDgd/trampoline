#ifndef __DETAILS_DNS_REQ_H__
#define __DETAILS_DNS_REQ_H__

#include "name.h"

typedef struct dns_req_form {
    ptr name      ,
        type      ,
        cls       ;
}   dns_req_form  ;

extern obj_trait dns_req_t;
typedef struct   dns_req  {
    obj          head;
    struct dns  *dns ;
    ptr          ptr ;
    dns_req_form form;
}   dns_req;

bool_t dns_req_do_init_from      (dns_req*)                ;
bool_t dns_req_do_init_from_param(dns_req*, va_list)       ;

bool_t dns_req_init              (dns_req*, u32_t, va_list);
bool_t dns_req_init_as_clone     (dns_req*, dns_req*)      ;
void   dns_req_deinit            (dns_req*)                ;
u64_t  dns_req_size              (dns_req*)                ;

#endif