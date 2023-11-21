#ifndef __DETAILS_DNS_BUILD_H__
#define __DETAILS_DNS_BUILD_H__

#include "v4.h"
#include "dns.h"

extern obj_trait __dns_builder_trait ;
typedef struct   __dns_builder       {
    obj    head      ;
    __dns *dns       ;
    u16_t  req       ,
           res       ,
           auth      ,
           additional;
}   __dns_builder;

bool_t __dns_builder_init         (__dns_builder*, u32_t, va_list);
bool_t __dns_builder_init_as_clone(__dns_builder*, __dns_builder*);
void   __dns_builder_deinit       (__dns_builder*)                ;
u64_t  __dns_builder_size         ()                              ;

bool_t __dns_build_from         (__dns_builder*, ptr)   ;
bool_t __dns_build_from_existing(__dns_builder*, __dns*);

bool_t __dns_build_head         (__dns_builder*, u16_t, u16_t)                          ;
bool_t __dns_build_req          (__dns_builder*, __dns_name*, u16_t, u16_t)             ;
bool_t __dns_build_res_a        (__dns_builder*, __dns_name*, u16_t, u32_t, u32_t)      ;
bool_t __dns_build_res_cname    (__dns_builder*, __dns_name*, u16_t, u32_t, __dns_name*);
__dns* __dns_build              (__dns_builder*)                                        ;

#endif