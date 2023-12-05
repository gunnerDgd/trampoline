#ifndef __ZONE_H__
#define __ZONE_H__

#include "rec.h"

typedef void* dns_zone;

str*    dns_zone_name     (dns_zone)             ;
dns_rec dns_rec_add       (dns_zone, str*)       ;
dns_rec dns_rec_add_cstr  (dns_zone, const char*);
void    dns_rec_del       (dns_zone, dns_rec)    ;
dns_rec dns_rec_get       (dns_zone, str*)       ;
dns_rec dns_rec_get_cstr  (dns_zone, const char*);

#endif