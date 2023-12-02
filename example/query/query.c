#include <run.h>
#include <async.h>
#include <udp.h>

#include "dns.h"
#include "req.h"
#include "res.h"

#include <stdio.h>
#include <intrin.h>

run()                                                  {
    v4  *udp_addr = make(v4_t)  from (2, "8.8.8.8", 53);
    v4  *res_addr = make(v4_t)  from (2, "1.1.1.1", 53);
    udp *udp      = make(udp_t) from (0)               ;
    box *box      = make(box_t) from (1, 512)          ;

    dns_flag dns_flag = { .rd = 1, .qr = 1 };
    obj*     dns      = make(dns_t) from (3, box, 1, dns_flag);
    str     *req      = make(str_t) from (0)                  ;

    str_push_back_cstr(req, "www.naver.com", 13);
    dns_res_a         (dns, dns_req_a(dns, req), 1000, res_addr);
    await (udp_send_to(udp, box_ptr(box, 0), dns_size(dns), udp_addr));

    /*del(dns);
    await(udp_recv(udp, box_ptr(box, 0), box_size(box)));
    
    dns_req res      = dns_res_from(dns);
    for ( ; res; res = dns_res_next(res))                             {
        if (dns_res_type(res) == 5)                                   {
            printf("CNAME REQ : %s\n", str_ptr(dns_res_req     (res)));
            printf("CNAME RES : %s\n", str_ptr(dns_res_as_cname(res)));
        }

        if (dns_res_type(res) == 1)                           {
            printf("A REQ : %s\n", str_ptr(dns_res_req (res)));
            printf("A RES : %s\n", str_ptr(dns_res_as_a(res)));
        }
    }

    del(dns);*/
}