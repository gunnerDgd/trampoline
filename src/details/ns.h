#ifndef __DETAILS_NS_H__
#define __DETAILS_NS_H__

#include <obj.h>
#include <list.h>

#include "../soa.h"

extern obj_trait ns_t;
typedef struct   ns  {
    obj  head;
    list zone;
}   ns;

bool_t    ns_new      (ns*, u32_t, va_list);
bool_t    ns_clone    (ns*, ns*)           ;
void      ns_del      (ns*)                ;

list_elem ns_zone_add (ns*, str*, dns_soa) ;
void      ns_zone_del (ns*, list_elem)     ;
list_elem ns_zone_get (ns*, str*)          ;
list_elem ns_find     (ns*, str*)          ;

#endif