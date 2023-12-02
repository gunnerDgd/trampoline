#include "head.h"
#include "dns.h"

#include "details/head.h"
#include "details/dns.h"

#include "endian.h"

dns_flag 
    dns_head_flag
        (obj* par)         {
            dns_flag ret = { .flag = 0 };

            if(!par)                   return ret;
            if(trait_of(par) != dns_t) return ret;

            ret.flag = head_flag(par);
            return ret;
}

u16_t
    dns_head_id
        (obj* par)                               {
            if (!par)                   return -1;
            if (trait_of(par) != dns_t) return -1;

            return head_id(par);
}