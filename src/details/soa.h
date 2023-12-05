#ifndef __DETAILS_SOA_H__
#define __DETAILS_SOA_H__

#include <obj.h>
#include <box.h>

#include "name.h"
#include "res.h"

extern obj_trait soa_t     ;
typedef struct   soa       {
    obj      head          ;
    name     mname  , rname;
    u32_t    serial ,
             refresh,
             retry  ,
             expire ,
             ttl    ;
}   soa;

bool_t soa_new_from(soa*, res*)          ;
bool_t soa_new     (soa*, u32_t, va_list);
bool_t soa_clone   (soa*, soa*)          ;
void   soa_del     (soa*)                ;

#endif