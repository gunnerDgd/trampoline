#ifndef __DNS_RES_H__
#define __DNS_RES_H__

#include "obj.h"

u16_t  dns_res_type(obj*);
u16_t  dns_res_cls (obj*);
u16_t  dns_res_ttl (obj*);
u16_t  dns_res_len (obj*);

obj*   dns_res_req	        (obj*);
u64_t  dns_res_data_len		(obj*);
str*   dns_res_data_as_a    (obj*);
obj*   dns_res_data_as_cname(obj*);

#endif