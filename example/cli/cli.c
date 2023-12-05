#include <run.h>

#include "cli.h"
#include "pkt.h"
#include "res.h"

#include "rslv.h"

#include <stdio.h>
#include <intrin.h>


run() {
    dns_cli cli = make(dns_cli_t) from(2, "8.8.8.8", 53);
    dns_cli_req_a_cstr(cli, "www.google.co.kr");
    dns_cli_req_a_cstr(cli, "www.naver.com")   ;

    dns_pkt pkt = await(dns_cli_req(cli));
    dns_res res = dns_pkt_res(pkt)       ;

    for (; res; res = dns_res_next(res)) {
        switch(dns_res_type(res))        {
        case 1:
            printf("A REQ : %s\n"  , str_ptr(dns_res_req (res)));
            printf("A RES : %s\n"  , str_ptr(dns_res_as_a(res)));
            break;
        case 5:
            printf("CNAME REQ : %s\n", str_ptr(dns_res_req     (res)));
            printf("CNAME RES : %s\n", str_ptr(dns_res_as_cname(res)));
            break;
        }
    }
    
    del(cli);
}