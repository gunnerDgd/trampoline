#include "dns.h"
#include "res.h"
#include "build.h"

#include "udp.h"
#include "io_sched.h"

#include <stdio.h>

io_sched_main(par, par_sched)                          {
    v4  *udp_addr = make(v4_t)  from (2, "8.8.8.8", 53);
    udp *udp      = make(udp_t) from (1, par_sched)    ;
    str *qry      = make(str_t) from (0)               ;
    str_push_back_cstr(qry, "www.naver.com", 13)       ;

    dns_builder*   builder = make(dns_builder_t) from (0);
    dns_build_head(builder, 1, 0x0100)                   ;
    dns_build_req (builder, qry, 1, 1)                   ;

    dns* dns         = dns_build(builder)   ;
    box* dns_pkt     = dns_mem  (dns)       ;
    ptr  dns_pkt_ptr = box_ptr  (dns_pkt, 0);

    task* snd = udp_send_to(udp, dns_pkt_ptr, dns_len(dns), udp_addr);
    await(snd);

    del(dns);
    task* rcv = udp_recv(udp, dns_pkt_ptr, ptr_size(dns_pkt_ptr));
    await(rcv);

    dns = make(dns_t) from (2, dns_pkt, 0);
    str* res = make(str_t) from(0);
    dns_res_for(dns, res_it)                                         {
        if (dns_res_as_a(get(res_it), res))                          {
            printf("A : %s\n", ptr_as(str_ptr(res), const char*))    ;
        }
        if (dns_res_as_cname(get(res_it), res))                      {
            printf("CNAME : %s\n", ptr_as(str_ptr(res), const char*));
        }

        del(res);
        res = make(str_t) from(0);
    }
}