#include "pkt.h"
#include "details/pkt.h"

#include "endian.h"

obj_trait* dns_pkt_t = &pkt_t;

u64_t
    dns_pkt_size
        (dns_pkt par)                               {
            if (!par)                       return 0;
            if (trait_of(par) != dns_pkt_t) return 0;

            return ((pkt*)par)->ptr_off - ((pkt*)par)->ptr;
}

void*
    dns_pkt_ptr
        (dns_pkt par)                               {
            if (!par)                       return 0;
            if (trait_of(par) != dns_pkt_t) return 0;

            return ((pkt*)par)->ptr;
}