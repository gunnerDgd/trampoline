#include <run.h>

#include "rslv.h"
#include "rslv_req.h"

#include <stdio.h>
#include <intrin.h>

#include <mysql/mysql.h>

run() {
    dns_rslv rslv = make(dns_rslv_t) from(2, "0.0.0.0", 53);
    while (true_t)                                  {    
        dns_rslv_req req = await(dns_rslv_run(rslv));
        while (dns_rslv_next(req))                                          {
            switch (dns_rslv_req_type(req))                                 {
                case 1 : dns_rslv_a_cstr    (req, 1000, "1.1.1.1")   ; break;
                case 5 : dns_rslv_cname_cstr(req, 1000, "lan.lan.ru"); break;
                case 12:
                case 6 : dns_rslv_ptr_cstr  (req, 1000, "lan.lan.ru"); break;
            }
        }

        await(dns_rslv_res(req));
    }
}