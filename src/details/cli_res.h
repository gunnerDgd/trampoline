#ifndef __DETAILS_CLI_RES_H__
#define __DETAILS_CLI_RES_H__

#include <obj.h>
#include <udp.h>
#include <async.h>

#include "../pkt.h"
#include "../res.h"

extern obj_trait cli_res_t;
typedef struct   cli_res  {
    obj         head   ;
    struct cli* cli    ;
    udp        *udp    ;
    dns_pkt     pkt    ;
    box        *pkt_box;
    dns_res     res    ;
    
}   cli_res;

cli_res* cli_res_main    (cli_res*)                ;
bool_t   cli_res_new     (cli_res*, u32_t, va_list);
bool_t   cli_res_clone   (cli_res*, cli_res*)      ;
void     cli_res_del     (cli_res*)                ;

bool_t   cli_res_next    (cli_res*);
str*     cli_res_req     (cli_res*);
u16_t    cli_res_type    (cli_res*);
u16_t    cli_res_cls     (cli_res*);
u32_t    cli_res_ttl     (cli_res*);

str*     cli_res_as_a    (cli_res*);
str*     cli_res_as_cname(cli_res*);
str*     cli_res_as_ptr  (cli_res*);
dns_soa  cli_res_as_soa  (cli_res*);

#endif