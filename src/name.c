#include "name.h"
#include "details/name.h"

dns_name    
    dns_name_new_from_cstr(const char* par) {
        str ret_str;
        if (!make_at(&ret_str, str_t) from(0)) return 0;

        name  *ret = make (&name_t) from (1, &ret_str); del(&ret_str);
        return ret;
}

dns_name    
    dns_name_new(str* par)                {
        return make(&name_t) from (1, par);
}

str* 
    dns_name_as_str
        (dns_name par)                            {
            if (!par)                     return 0;
            if (trait_of(par) != &name_t) return 0;

            return name_as_str(par);
}