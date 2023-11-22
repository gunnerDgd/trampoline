#ifndef __DNS_H__
#define __DNS_H__

#include "obj.h"
#include "box.h"
#include "it.h"

typedef union dns_flag {
    u16_t    flag      ;
    struct             {
        u8_t rcode  : 4;
        u8_t cd     : 1;
        u8_t ad     : 1;
        u8_t z      : 1;
        u8_t ra     : 1;
        u8_t rd     : 1;
        u8_t tc     : 1;
        u8_t aa     : 1;
        u8_t opcode : 4;
        u8_t qr     : 1;
    };
}   dns_flag;

obj*     dns_new      (ptr, u16_t, dns_flag);
obj*     dns_new_from (ptr)                 ;
u64_t    dns_len      (obj*)                ;

u16_t    dns_head_id  (obj*);
dns_flag dns_head_flag(obj*);

it       dns_req_begin(obj*);
it       dns_req_end  (obj*);
u16_t    dns_req_count(obj*);

it       dns_res_begin(obj*);
it       dns_res_end  (obj*);
u16_t    dns_res_count(obj*);

#define dns_req_for(par_dns, par_it)                                        \
    it par_it = dns_req_begin(par_dns), par_it##_end = dns_req_end(par_dns);\
    for( ; neq(par_it, par_it##_end) ; next(par_it))                        \

#define dns_res_for(par_dns, par_it)                                        \
    it par_it = dns_res_begin(par_dns), par_it##_end = dns_res_end(par_dns);\
    for( ; neq(par_it, par_it##_end) ; next(par_it))                        \

#endif