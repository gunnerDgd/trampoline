#ifndef __DETAILS_DNS_NAME_H__
#define __DETAILS_DNS_NAME_H__

#include <obj.h>
#include <list.h>
#include <str.h>

extern obj_trait name_t;
typedef struct   name  {
    obj head;
    str name;
}   name;

bool_t      name_new         (name*, u32_t, va_list)    ;
bool_t      name_new_from_str(name*, str*)              ;
bool_t      name_new_from_pkt(name*, struct dns*, u8_t*);
bool_t      name_clone       (name*, name*)             ;
void        name_del         (name*)                    ;
u64_t       name_len         (name*)                    ;
const char* name_ptr         (name*)                    ;
str*        name_as_str      (name*)                    ;

#endif