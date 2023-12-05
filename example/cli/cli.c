#include <run.h>

#include "cli.h"
#include "cli_res.h"

#include "pkt.h"
#include "res.h"

#include "rslv.h"

#include <stdio.h>
#include <intrin.h>


run() {
    dns_cli cli = make(dns_cli_t) from(2, "8.8.8.8", 53);
    dns_cli_req_a_cstr(cli, "www.naver.com");

    dns_cli_res res = await(dns_cli_req(cli));
    while     (dns_cli_res_next(res)) {
        obj* req  = 0;
        obj* data = 0;
        switch(dns_cli_res_type(res)) {
        case 1:
            printf("A REQ : %s\n", str_ptr(req  = dns_cli_res_req (res)));
            printf("A RES : %s\n", str_ptr(data = dns_cli_res_as_a(res)));
            break;
        case 5:
            printf("CNAME REQ : %s\n", str_ptr(req = dns_cli_res_req(res)), str_ptr(data = dns_cli_res_as_cname(res)));
            printf("CNAME RES : %s\n", str_ptr(req = dns_cli_res_req(res)), str_ptr(data = dns_cli_res_as_cname(res)));
            break;
        }

        del(req) ;
        del(data);
    }
    
    del(res);
    del(cli);
}