#ifndef __DETAILS_DNS_NAME_H__
#define __DETAILS_DNS_NAME_H__

#include "obj.h"
#include "box.h"
#include "str.h"
#include "list.h"

extern obj_trait dns_name_t;
typedef struct   dns_name  {
    obj head  ;
    str name  ;
}   dns_name;

bool_t dns_name_init         (dns_name*, u32_t, va_list);
bool_t dns_name_init_as_clone(dns_name*, dns_name*)     ;
void   dns_name_deinit       (dns_name*)                ;
u64_t  dns_name_size         ()                         ;

bool_t dns_name_from_str     (dns_name*, str*)    ;
bool_t dns_name_from_ptr     (dns_name*, ptr, ptr);
str*   dns_name_to_str       (dns_name*)          ;
ptr    dns_name_to_ptr       (dns_name*, ptr, ptr);

u64_t  dns_name_len          (dns_name*);
u64_t  dns_name_len_from_ptr (ptr)      ;

#endif