#ifndef __DETAILS_RES_H__
#define __DETAILS_RES_H__

#include <obj.h>
#include <str.h>
#include <list.h>

#include <v4.h>

extern obj_trait rdata_t;
typedef struct   rdata  {
    obj   head;
    u64_t type;
    u64_t cls ;
    u64_t ttl ;
    u64_t pri ;
    union        {
        obj obj  ;
        v4  v4   ;
        str str  ;

        v4  a    ;
        str cname;
        str ptr  ;
        str mx   ;
    };
}   rdata;

bool_t rdata_new  (rdata*, u32_t, va_list);
bool_t rdata_clone(rdata*, rdata*)        ;
void   rdata_del  (rdata*)                ;

extern obj_trait rec_t;
typedef struct   rec  {
    obj          head ;
    struct zone *zone ;
    str          rec  ;
    list         data ;
}   rec;

bool_t rec_new  (rec*, u32_t, va_list);
bool_t rec_clone(rec*, rec*)          ;
void   rec_del  (rec*)                ;

#endif