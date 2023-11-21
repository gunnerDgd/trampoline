#ifndef __DNS_H__
#define __DNS_H__

#include "obj.h"
#include "box.h"
#include "it.h"

u64_t dns_len       (obj*);
obj*  dns_head      (obj*);

it    dns_req_begin (obj*);
it    dns_req_end   (obj*);
u16_t dns_req_count (obj*);

it    dns_res_begin (obj*);
it    dns_res_end   (obj*);
u16_t dns_res_count (obj*);

#define dns_req_for(par_dns, par_it)                                        \
    it par_it = dns_req_begin(par_dns), par_it##_end = dns_req_end(par_dns);\
    for( ; neq(par_it, par_it##_end) ; next(par_it))                        \

#define dns_res_for(par_dns, par_it)                                        \
    it par_it = dns_res_begin(par_dns), par_it##_end = dns_res_end(par_dns);\
    for( ; neq(par_it, par_it##_end) ; next(par_it))                        \

#endif