#ifndef __DNS_REQ_H__
#define __DNS_REQ_H__

#include "obj.h"

u16_t dns_req_type(obj*);
u16_t dns_req_cls (obj*);
u16_t dns_req_len (obj*);
obj*  dns_req_name(obj*);

#endif