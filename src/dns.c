#include "dns.h"
#include "details/dns.h"

#include "endian.h"

obj_trait* dns_t = &dns_trait;

u64_t
    dns_size
        (obj* par)                              {
            if (!par)                   return 0;
            if (trait_of(par) != dns_t) return 0;

            return ((dns*)par)->ptr_off - ((dns*)par)->ptr;
}