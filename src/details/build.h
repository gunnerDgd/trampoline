#ifndef __DETAILS_DNS_BUILD_H__
#define __DETAILS_DNS_BUILD_H__

#include "dns.h"

extern obj_trait __dns_builder_trait ;
typedef struct   __dns_builder       {
    obj    head                      ;
    alloc *alloc                     ;
    __dns *dns                       ;
    box   *mem                       ;
    u16_t  req, res, auth, additional;
}   __dns_builder;

bool_t __dns_builder_init         (__dns_builder*, u32_t, va_list);
bool_t __dns_builder_init_as_clone(__dns_builder*, __dns_builder*);
void   __dns_builder_deinit       (__dns_builder*)                ;
u64_t  __dns_builder_size         ()                              ;

bool_t __dns_build_head(__dns_builder*, u16_t, u16_t)                    ;
bool_t __dns_build_req (__dns_builder*, str* , u16_t, u16_t)             ;
bool_t __dns_build_res (__dns_builder*, str* , u16_t, u16_t, u16_t, str*);
__dns* __dns_build     (__dns_builder*)                                  ;

#endif