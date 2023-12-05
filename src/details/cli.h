#ifndef __DETAILS_CLI_H__
#define __DETAILS_CLI_H__

#include <obj.h>
#include <udp.h>
#include <async.h>

#include "../name.h"
#include "../head.h"
#include "../pkt.h"
#include "../req.h"
#include "../res.h"

extern obj_trait cli_t;
typedef struct   cli  {
    obj     head   ;
    v4      addr   ;
    dns_pkt pkt    ;
    box    *pkt_box;
}   cli;

bool_t cli_new           (cli*, u32_t, va_list);
bool_t cli_clone         (cli*, cli*)          ;
void   cli_del           (cli*)                ;
task   cli_req           (cli*)                ;

void   cli_req_a         (cli*, str*)          ;
void   cli_req_a_cstr    (cli*, const char*)   ;

void   cli_req_cname     (cli*, str*)          ;
void   cli_req_cname_cstr(cli*, const char*)   ;

void   cli_req_ptr       (cli*, v4*)           ;
void   cli_req_ptr_str   (cli*, str*)          ;
void   cli_req_ptr_cstr  (cli*, const char*)   ;

void   cli_req_soa       (cli*, str*)          ;
void   cli_req_soa_cstr  (cli*, const char*)   ;

#endif