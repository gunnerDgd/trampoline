#ifndef __RSLV_H__
#define __RSLV_H__

#include <obj.h>
#include <task.h>

#include "req.h"
#include "res.h"
#include "soa.h"
#include "cli.h"

extern obj_trait* dns_rslv_t  ;
typedef obj*      dns_rslv    ;

task dns_rslv_run(dns_rslv);

#endif