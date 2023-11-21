#include "head.h"
#include "details/head.h"

#include "endian.h"

obj_trait *dns_head_t = &__dns_head_trait;

u16_t 
    dns_id
        (obj* par)                                    {
            if (!par)                        return -1;
            if (trait_of(par) != dns_head_t) return -1;

            return be16(((__dns_head*)par)->form->id);
}

u16_t 
    dns_opcode
        (obj* par)                                       {
            if (!par)                           return -1;
            if (trait_of(par) != dns_head_t)    return -1;

            return be16(((__dns_head*)par)->form->opcode);
}