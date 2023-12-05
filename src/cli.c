#include "cli.h"
#include "details/cli.h"

#include <string.h>

obj_trait* dns_cli_t = &cli_t;

task 
    dns_cli_req
        (dns_cli par)                               {
            if (!par)                       return 0;
            if (trait_of(par) != dns_cli_t) return 0;

            return cli_req (par);
}


void
    dns_cli_req_a     
        (dns_cli par, str* par_req)               {
            if (!par)                       return;
            if (trait_of(par) != dns_cli_t) return;

            cli_req_a(par, par_req);
}

void
    dns_cli_req_a_cstr
        (dns_cli par, const char* par_req)        { 
            if (!par)                       return;
            if (trait_of(par) != dns_cli_t) return;

            cli_req_a_cstr(par, par_req);
}

void
    dns_cli_req_cname
        (dns_cli par, str* par_req)               { 
            if (!par)                       return;
            if (trait_of(par) != dns_cli_t) return;

            cli_req_cname(par, par_req);
}

void
    dns_cli_req_cname_cstr
        (dns_cli par, const char* par_req)        { 
            if (!par)                       return;
            if (trait_of(par) != dns_cli_t) return;

            cli_req_cname_cstr(par, par_req);
}

void 
    dns_cli_req_ptr
        (dns_cli par, v4* par_req)               {
            if (!par)                       return;
            if (trait_of(par) != dns_cli_t) return;

            cli_req_ptr(par, par_req);
}

void 
    dns_cli_req_ptr_str
        (dns_cli par, str* par_req)               {
            if (!par)                       return;
            if (trait_of(par) != dns_cli_t) return;

            cli_req_ptr_str(par, par_req);
}

void 
    dns_cli_req_ptr_cstr
        (dns_cli par, const char* par_req)        {
            if (!par)                       return;
            if (trait_of(par) != dns_cli_t) return;

            cli_req_ptr_cstr(par, par_req);
}

void
    dns_cli_req_soa
        (dns_cli par, str* par_req)               { 
            if (!par)                       return;
            if (trait_of(par) != dns_cli_t) return;

            cli_req_soa(par, par_req);
}

void
    dns_cli_req_soa_cstr
        (dns_cli par, const char* par_req)        { 
            if (!par)                       return;
            if (trait_of(par) != dns_cli_t) return;

            cli_req_soa_cstr(par, par_req);
}