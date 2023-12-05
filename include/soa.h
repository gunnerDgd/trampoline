#ifndef __SOA_H__
#define __SOA_H__

#include <obj.h>

extern  obj_trait *dns_soa_t;
typedef obj       *dns_soa  ;

str*  dns_soa_mname (dns_soa);
str*  dns_soa_rname (dns_soa);
u32_t dns_soa_serial(dns_soa);
u32_t dns_soa_retry (dns_soa);
u32_t dns_soa_expire(dns_soa);
u32_t dns_soa_ttl   (dns_soa);

#endif