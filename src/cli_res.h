#ifndef __CLI_RES_H__
#define __CLI_RES_H__

#include <obj.h>
#include "soa.h"

typedef obj* dns_cli_res;

bool_t  dns_cli_res_next      (dns_cli_res);
str*    dns_cli_res_req       (dns_cli_res);
u16_t   dns_cli_res_type      (dns_cli_res);
u16_t   dns_cli_res_cls       (dns_cli_res);
u32_t   dns_cli_res_ttl       (dns_cli_res);

str*    dns_cli_res_as_a      (dns_cli_res);
str*    dns_cli_res_as_cname  (dns_cli_res);
str*    dns_cli_res_as_ptr    (dns_cli_res);
dns_soa dns_cli_res_as_soa    (dns_cli_res);

#endif