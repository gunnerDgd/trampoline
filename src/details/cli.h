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

typedef struct cli_task {
    struct cli *cli ;
    dns_pkt     pkt ;
    task        task;
}   cli_task;

extern obj_trait cli_t;
typedef struct   cli  {
    obj     head;
    udp     cli ;
    v4      addr;
    dns_pkt pkt ;
}   cli;

bool_t cli_new  (cli*, u32_t, va_list);
bool_t cli_clone(cli*, cli*)          ;
void   cli_del  (cli*)                ;
task   cli_req  (cli*)                ;

#endif