#ifndef __DNS_H__
#define __DNS_H__

#include "obj.h"
#include "box.h"
#include "it.h"

extern obj_trait* dns_t;
typedef struct    dns { u8_t dns[1024]; } dns;

u16_t dns_id       (dns*);
u16_t dns_opcode   (dns*);
u64_t dns_len      (dns*);
box*  dns_mem      (dns*);

it    dns_req_begin(dns*);
it    dns_req_end  (dns*);
u16_t dns_req_count(dns*);

it    dns_res_begin(dns*);
it    dns_res_end  (dns*);
u16_t dns_res_count(dns*);

#define dns_req_for(par_dns, par_it)                                        \
    it par_it = dns_req_begin(par_dns), par_it##_end = dns_req_end(par_dns);\
    for( ; neq(par_it, par_it##_end) ; next(par_it))                        \

#define dns_res_for(par_dns, par_it)                                        \
    it par_it = dns_res_begin(par_dns), par_it##_end = dns_res_end(par_dns);\
    for( ; neq(par_it, par_it##_end) ; next(par_it))                        \

#endif