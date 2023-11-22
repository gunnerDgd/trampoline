#include "dns.h"
#include "dns/a.h"
#include "dns/cname.h"

#include "res.h"
#include "name.h"

#include "udp.h"
#include "io_sched.h"

#include <stdio.h>
#include <intrin.h>

io_sched_main(par, par_sched)                          {
    printf("Begin");
    v4  *udp_addr = make(v4_t)  from (2, "8.8.8.8", 53);
    udp *udp      = make(udp_t) from (1, par_sched)    ;

    box*     box      = make(box_t) from(1, 512);
    dns_flag dns_flag = { 
        .rd = 1
    };
    obj*     dns      = dns_new(box_ptr(box, 0), 1, dns_flag);

    dns_req_a_cstr(dns, "www.naver.com", 13, 1);

    printf("Send\n");
    task *snd = udp_send_to(udp, box_ptr(box, 0), dns_len(dns), udp_addr);
    printf("Sent\n");
    await(snd);

    del  (dns);
    printf("Receive\n");
    task* rcv = udp_recv(udp, box_ptr(box, 0), box_size(box));
    printf("Received\n");
    await(rcv);

    u64_t begin = __rdtsc();
    dns = dns_new_from(box_ptr(box, 0));
    u64_t end = __rdtsc();

    dns_res_for(dns, res_it)                    {
        obj* res     = get(res_it)              ;
        str* res_str = dns_res_as_cname_str(res);

        if (res_str)
            printf("%s\n", ptr_as(str_ptr(res_str), const char*));
    }

    del(dns);
}