#ifndef __DNS_H__
#define __DNS_H__

#include <obj.h>
#include <box.h>

#include "head.h"

typedef obj      *dns_pkt  ;
extern obj_trait *dns_pkt_t;
void*             dns_pkt_ptr (dns_pkt);
u64_t             dns_pkt_size(dns_pkt);

#endif