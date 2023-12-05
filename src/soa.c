#include "soa.h"
#include "details/soa.h"

#include <endian.h>

obj_trait* dns_soa_t = &soa_t;

str* 
    dns_soa_mname
        (dns_soa par)                              {
            if(!par)                       return 0;
            if(trait_of(par) != dns_soa_t) return 0;

            return name_as_str(&((soa*)par)->mname);
}

str* 
    dns_soa_rname
        (dns_soa par)                              {
            if(!par)                       return 0;
            if(trait_of(par) != dns_soa_t) return 0;

            return name_as_str(&((soa*)par)->rname);
}

u32_t 
    dns_soa_serial
        (dns_soa par)                              {
            if(!par)                       return 0;
            if(trait_of(par) != dns_soa_t) return 0;

            return be32(((soa*)par)->serial);
}

u32_t 
    dns_soa_retry
        (dns_soa par)                              {
            if(!par)                       return 0;
            if(trait_of(par) != dns_soa_t) return 0;

            return be32(((soa*)par)->retry);
}

u32_t 
    dns_soa_expire
        (dns_soa par)                              {
            if(!par)                       return 0;
            if(trait_of(par) != dns_soa_t) return 0;

            return be32(((soa*)par)->expire);
}

u32_t 
    dns_soa_ttl
        (dns_soa par)                              {
            if(!par)                       return 0;
            if(trait_of(par) != dns_soa_t) return 0;

            return be32(((soa*)par)->ttl);
}