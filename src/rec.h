#ifndef __REC_H__
#define __REC_H__

#include <obj.h>
#include <v4.h>

typedef void* dns_rec  ;
typedef void* dns_rdata;

str*      dns_rec_name        (dns_rec)  ;
dns_rdata dns_rec_data        (dns_rec)  ;

dns_rdata dns_rdata_next      (dns_rdata);
u16_t     dns_rdata_type      (dns_rdata);
u16_t     dns_rdata_cls       (dns_rdata);
u32_t     dns_rdata_ttl       (dns_rdata);
u64_t     dns_rdata_pri       (dns_rdata);

v4*       dns_rdata_as_a      (dns_rdata);
str*      dns_rdata_as_cname  (dns_rdata);
str*      dns_rdata_as_ptr    (dns_rdata);

dns_rdata dns_rdata_a         (dns_rec, u32_t, v4*)        ;
dns_rdata dns_rdata_a_str     (dns_rec, u32_t, str*)       ;
dns_rdata dns_rdata_a_cstr    (dns_rec, u32_t, const char*);

dns_rdata dns_rdata_cname     (dns_rec, u32_t, str*)       ;
dns_rdata dns_rdata_cname_cstr(dns_rec, u32_t, const char*);

dns_rdata dns_rdata_ptr       (dns_rec, u32_t, str*)       ;
dns_rdata dns_rdata_ptr_cstr  (dns_rec, u32_t, const char*);

#endif