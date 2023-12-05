#ifndef __NS_H__
#define __NS_H__

#include <obj.h>

#include "zone.h"
#include "soa.h"

extern obj_trait *dns_ns_t;
typedef obj      *dns_ns  ;

dns_rec  dns_ns_find      (dns_ns, str*)                ;
dns_rec  dns_ns_find_cstr (dns_ns, const char*)         ;

dns_zone dns_zone_add     (dns_ns, str*       , dns_soa);
dns_zone dns_zone_add_cstr(dns_ns, const char*, dns_soa);
void     dns_zone_del     (dns_ns, dns_zone)            ;
dns_zone dns_zone_get     (dns_ns, str*)                ;
dns_zone dns_zone_get_cstr(dns_ns, const char*)         ;

#endif