#ifndef __DETAILS_ZONE_H__
#define __DETAILS_ZONE_H__

#include <obj.h>
#include <list.h>

#include "../soa.h"

extern obj_trait zone_t;
typedef struct   zone  {
    obj        head;
    str        zone;
    struct ns* ns  ;
    list       rec ;
    dns_soa    soa ;
}   zone;

bool_t    zone_new    (zone*, u32_t, va_list);
bool_t    zone_clone  (zone*, zone*)         ;
void      zone_del    (zone*)                ;

list_elem zone_rec_add(zone*, str*)     ;
void      zone_rec_del(zone*, list_elem);
list_elem zone_rec_get(zone*, str*)     ;

#endif