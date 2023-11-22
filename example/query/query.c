#include "dns.h"
#include "res.h"
#include "build.h"
#include "build/a.h"

#include "parse.h"
#include "head.h"
#include "name.h"

#include "udp.h"
#include "io_sched.h"

#include <stdio.h>

io_sched_main(par, par_sched)                          {
    v4  *udp_addr = make(v4_t)  from (2, "8.8.8.8", 53);
    udp *udp      = make(udp_t) from (1, par_sched)    ;

    box* box      = make(box_t) from(1, 512)       ;
    obj* builder  = dns_build_from(box_ptr(box, 0));

    if (!dns_build_head      (builder, 1, 0x0100))              { printf("Build Failed (HEAD)\n"); return 1; }
    if (!dns_build_req_a_cstr(builder, "www.naver.com", 13, 1)) { printf("Build Failed (REQ)\n") ; return 1; }

    obj  *dns = dns_build(builder);
    if(!dns)                      {
        printf("Build Failed\n")  ;
        return 1;
    }

    task *snd = udp_send_to(udp, box_ptr(box, 0), dns_len(dns), udp_addr);
    await(snd);

    del(dns);
    task* rcv = udp_recv(udp, box_ptr(box, 0), box_size(box));
    await(rcv);
        
    obj* parser = dns_parse_from(box_ptr(box, 0));
    dns         = dns_parse     (parser)         ;

    dns_res_for(dns, res_it)                                      {
        obj* res     = get(res_it)                                ;
        str* res_str = dns_name_to_str(dns_res_data_as_cname(res));

        if (res_str)
            printf("%s\n", ptr_as(str_ptr(res_str), const char*));
    }
}