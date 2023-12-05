#ifndef __DNS_HEAD_H__
#define __DNS_HEAD_H__

#include <obj.h>

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

dns_flag dns_head_flag(obj*);
u16_t    dns_head_id  (obj*);

#endif