#include "build.h"
#include "details/build.h"

obj_trait* dns_builder_t = &__dns_builder_trait;

obj* 
    dns_build_from
        (ptr par)                                 {
            obj* ret = make(dns_builder_t) from(0);
            if (!ret)               return false_t;
            if (!__dns_build_from(ret, par))      {
                del(ret);
                return 0;
            }

            return ret;
}

obj* 
    dns_build_from_existing
        (obj* par)                                           {
            if (!par)                          return false_t;
            if (trait_of(par) != &__dns_trait) return false_t;

            obj* ret = make(dns_builder_t) from(0);
            if (!ret)                   return false_t;
            if (!__dns_build_from_existing(ret, par)) {
                del(ret);
                return 0;
            }

            return ret;
}

bool_t 
    dns_build_head
        (obj* par, u16_t par_id, u16_t par_opcode)            {
            if (!par)                           return false_t;
            if (trait_of(par) != dns_builder_t) return false_t;

            return __dns_build_head(par, par_id, par_opcode);
}

obj*
    dns_build
        (obj* par)                                            {
            if (!par)                           return false_t;
            if (trait_of(par) != dns_builder_t) return false_t;

            return __dns_build(par);
}