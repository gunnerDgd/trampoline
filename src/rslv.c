#include "rslv.h"
#include "details/rslv.h"

obj_trait* dns_rslv_t = &rslv_t;

task 
    dns_rslv_run
        (dns_rslv par)                               {
            if (!par)                        return 0;
            if (trait_of(par) != dns_rslv_t) return 0;

            return rslv_run(par);
}