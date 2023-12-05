#include "res.h"
#include "req.h"
#include "pkt.h"

#include "ns.h"
#include "zone.h"
#include "rec.h"
#include "soa.h"

#include <stdio.h>

#include <async.h>
#include <run.h>

run()                               {
    str* mname = make(str_t) from(0); str_push_back_cstr(mname, "lan.lan.ru", 10);
    str* rname = make(str_t) from(0); str_push_back_cstr(rname, "lan.lan.ru", 10);

    dns_ns   ns   = make(dns_ns_t)  from (0);
    dns_soa  soa  = make(dns_soa_t) from (
        7     ,
        mname ,
        rname ,
        1     ,
        3600  ,
        1200  ,
        604800,
        10800
    );

    dns_zone  zone     = dns_zone_add_cstr(ns, "lan.ru", soa)   ;
    dns_rec   rec      = dns_rec_add_cstr (zone, "lan")         ;
    dns_rdata rdata    = dns_rdata_a_cstr (rec, 1000, "1.1.1.1");
    
    dns_rec  rec_found = dns_ns_find_cstr(ns, "lan.lan.ru");
    dns_rdata rdata_found = dns_rec_data(rec_found);

    for ( ; rdata_found ; rdata_found = dns_rdata_next(rdata_found)) {
        printf("TTL : %d / TYPE : %d", dns_rdata_ttl(rdata_found), dns_rdata_type(rdata_found));
    }
}