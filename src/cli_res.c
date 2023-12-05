#include "cli_res.h"
#include "details/cli_res.h"

bool_t 
    dns_cli_res_next
        (dns_cli_res par)                                  {
            if (!par)                        return false_t;
            if (trait_of(par) != &cli_res_t) return false_t;

            return cli_res_next(par);
}

str* 
    dns_cli_res_req
        (dns_cli_res par)                            {
            if (!par)                        return 0;
            if (trait_of(par) != &cli_res_t) return 0;

            return cli_res_req(par);
}

u16_t   
    dns_cli_res_type
        (dns_cli_res par)                             {
            if (!par)                        return -1;
            if (trait_of(par) != &cli_res_t) return -1;

            return cli_res_type(par);
}

u16_t   
    dns_cli_res_cls
        (dns_cli_res par)                             {
            if (!par)                        return -1;
            if (trait_of(par) != &cli_res_t) return -1;

            return cli_res_cls(par);
}

u32_t
    dns_cli_res_ttl
        (dns_cli_res par)                             {
            if (!par)                        return -1;
            if (trait_of(par) != &cli_res_t) return -1;

            return cli_res_ttl(par);
}

str* 
    dns_cli_res_as_a
        (dns_cli_res par)                            {
            if (!par)                        return 0;
            if (trait_of(par) != &cli_res_t) return 0;

            return cli_res_as_a(par);
}

str* 
    dns_cli_res_as_cname
        (dns_cli_res par)                            {
            if (!par)                        return 0;
            if (trait_of(par) != &cli_res_t) return 0;

            return cli_res_as_cname(par);
}

str* 
    dns_cli_res_as_ptr
        (dns_cli_res par)                            {
            if (!par)                        return 0;
            if (trait_of(par) != &cli_res_t) return 0;

            return cli_res_as_ptr(par);
}

dns_soa 
    dns_cli_res_as_soa
        (dns_cli_res par)                            {
            if (!par)                        return 0;
            if (trait_of(par) != &cli_res_t) return 0;

            return cli_res_as_soa(par);
}