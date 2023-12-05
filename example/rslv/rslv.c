#include <run.h>

#include "cli.h"
#include "pkt.h"
#include "res.h"
#include "soa.h"

#include "rslv.h"
#include "ns.h"

#include <stdio.h>
#include <intrin.h>

#include <mysql/mysql.h>

run() {
    dns_cli  cli       = make(dns_cli_t) from(2, "8.8.8.8", 53);
    dns_ns   ns        = make(dns_ns_t)  from(0);
    str*     soa_mname = make(str_t)     from(0); str_push_back_cstr(soa_mname, "LANLANRU"         , 8) ;
    str*     soa_rname = make(str_t)     from(0); str_push_back_cstr(soa_rname, "LANLANRU.LANLANRU", 17);
    dns_soa  soa       = make(dns_soa_t) from(
        7        ,
        soa_mname,
        soa_rname,
        1        ,
        3600     ,
        1200     ,
        604800   ,
        10800
    );

    dns_zone  zone     = dns_zone_add_cstr(ns, "naver.com", soa);
    dns_rec   rec      = dns_rec_add_cstr (zone, "www")         ;
    dns_rdata_a_cstr (rec , 1000, "2.2.2.2");
    dns_rdata_a_cstr (rec , 1000, "3.3.3.3");
    dns_rdata_a_cstr (rec , 1000, "4.4.4.4");
    dns_rslv  rslv     = make(dns_rslv_t) from(3, ns, "0.0.0.0", 53);
    while (true_t)                                         {    
        dns_rslv_task rslv_task = await(dns_rslv_run(rslv));
        rslv_task = await(dns_rslv_res(rslv_task));
        if (!rslv_task) {
            continue;
        }

        while (true_t)                            {
            switch (dns_rslv_req_type(rslv_task)) {
            case 1 :
            case 5 : printf("A / CNAME\n"); dns_rslv_a_cstr  (rslv_task, 1000, "1.1.1.1"); break;
            case 12: printf("PTR\n")      ; dns_rslv_ptr_cstr(rslv_task, 1000, "lan.lan.ru"); break;
            case 6 : printf("SOA\n")      ; dns_rslv_soa     (rslv_task, 1000, soa);       break;
            }

            if (!dns_rslv_next(rslv_task))
                break;
        }

        await(dns_rslv_res(rslv_task));
    }
}