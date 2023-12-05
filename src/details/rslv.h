#ifndef __DETAILS_RSLV_H__
#define __DETAILS_RSLV_H__

#include <obj.h>
#include <udp.h>
#include <async.h>

#include <list.h>
#include <box.h>

#include "rslv_req.h"
#include "../ns.h"
#include "../cli.h"

extern obj_trait rslv_t;
typedef struct   rslv  {
    obj head;
    v4  addr;
}   rslv;

bool_t    rslv_new     (rslv*, u32_t, va_list);
bool_t    rslv_clone   (rslv*, rslv*)         ;
void      rslv_del     (rslv*)                ;
rslv_req* rslv_run_main(rslv*)                ;
task      rslv_run     (rslv*)                ;

#endif