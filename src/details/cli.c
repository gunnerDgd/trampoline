#include "cli.h"
#include "cli_res.h"

#include "../name.h"
#include "../pkt.h"
#include "../req.h"
#include "../res.h"

obj_trait cli_t         = {
    .on_new   = &cli_new  ,
    .on_clone = &cli_clone,
    .on_del   = &cli_del  ,
    .size     = sizeof(cli)
};

bool_t 
    cli_new
        (cli* par_cli, u32_t par_count, va_list par) {
            switch (par_count)              {
            case 1:                         {
                v4  *addr = va_arg(par, v4*);
                if (!addr)                           return false_t;
                if (trait_of(addr) != v4_t)          return false_t;
                if (!clone_at(&par_cli->addr, addr)) return false_t;
                break;
            }
            case 2:                                        {
                const char* addr = va_arg(par, const char*);
                u16_t       port = va_arg(par, u16_t)      ;

                if (!make_at(&par_cli->addr, v4_t) from(2, addr, port)) return false_t;
                break;
            }
            default: return false_t;
            }

            dns_flag pkt_flag = { .rd = 1 };
            par_cli->pkt_box  = make(box_t)     from (1, 512)                          ; if (!par_cli->pkt_box) goto new_failed;
            par_cli->pkt      = make(dns_pkt_t) from (3, par_cli->pkt_box, 1, pkt_flag); if (!par_cli->pkt)     goto new_failed;

            return true_t;
    new_failed:
            if (par_cli->pkt)     del(par_cli->pkt)    ;
            if (par_cli->pkt_box) del(par_cli->pkt_box);
            return false_t       ;

}

bool_t 
    cli_clone
        (cli* par, cli* par_clone) { 
            return false_t; 
}

void
    cli_del
        (cli* par)            {
            del (par->pkt)    ;
            del (par->pkt_box);
            del(&par->addr)   ;
}

task   
    cli_req
        (cli* par)            {
            cli_res* ret_res  = make (&cli_res_t) from (3, ref(par), par->pkt, par->pkt_box);
            task     ret      = async(cli_res_main, ret_res);

            dns_flag pkt_flag = { .rd = 1 };
            par->    pkt_box  = make(box_t)     from (1, 512)                      ;
            par->    pkt      = make(dns_pkt_t) from (3, par->pkt_box, 1, pkt_flag);
            return   ret;
}

void   cli_req_a         (cli* par, str*        par_str) { dns_req_a         (par->pkt, par_str); }
void   cli_req_a_cstr    (cli* par, const char* par_str) { dns_req_a_cstr    (par->pkt, par_str); }

void   cli_req_cname     (cli* par, str*        par_str) { dns_req_cname     (par->pkt, par_str); }
void   cli_req_cname_cstr(cli* par, const char* par_str) { dns_req_cname_cstr(par->pkt, par_str); }

void   cli_req_ptr       (cli* par, v4*         par_v4)  { dns_req_ptr       (par->pkt, par_v4) ; }
void   cli_req_ptr_str   (cli* par, str*        par_str) { dns_req_ptr_str   (par->pkt, par_str); }
void   cli_req_ptr_cstr  (cli* par, const char* par_str) { dns_req_ptr_cstr  (par->pkt, par_str); }

void   cli_req_soa       (cli* par, str*        par_str) { dns_req_soa       (par->pkt, par_str); }
void   cli_req_soa_cstr  (cli* par, const char* par_str) { dns_req_soa_cstr  (par->pkt, par_str); }