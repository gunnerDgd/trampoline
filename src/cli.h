#ifndef __CLI_H__
#define __CLI_H__

#include <obj.h>
#include <async.h>
#include <v4.h>

#include "pkt.h"
#include "soa.h"

extern obj_trait* dns_cli_t  ;
typedef obj*      dns_cli    ;

task dns_cli_req           (dns_cli)             ;

void dns_cli_req_a         (dns_cli, str*)       ;
void dns_cli_req_a_cstr    (dns_cli, const char*);

void dns_cli_req_cname     (dns_cli, str*)       ;
void dns_cli_req_cname_cstr(dns_cli, const char*);

void dns_cli_req_ptr       (dns_cli, v4*)        ;
void dns_cli_req_ptr_str   (dns_cli, str*)       ;
void dns_cli_req_ptr_cstr  (dns_cli, const char*);

void dns_cli_req_soa       (dns_cli, str*)       ;
void dns_cli_req_soa_cstr  (dns_cli, const char*);

#endif