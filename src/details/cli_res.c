#include "cli_res.h"
#include "cli.h"

obj_trait cli_res_t         = {
    .on_new   = &cli_res_new  ,
    .on_clone = &cli_res_clone,
    .on_ref   = 0             ,
    .on_del   = &cli_res_del  ,
    .size     = sizeof(cli_res)
};

cli_res*
    cli_res_main
        (cli_res* par)                             {
            u8_t* ptr      = box_ptr (par->pkt_box);
            u64_t ptr_size = box_size(par->pkt_box);

            if (!await(udp_send_to  (par->udp, ptr, ptr_size, &par->cli->addr))) goto main_failed;
            if (!await(udp_recv_from(par->udp, ptr, ptr_size, &par->cli->addr))) goto main_failed;
            if (!(par->pkt = make (dns_pkt_t) from (1, par->pkt_box)))           goto main_failed;

            return par;
    main_failed:
        del(par);
        return 0;
}

bool_t  
    cli_res_new
        (cli_res* par_cli, u32_t par_count, va_list par) {
            if (!(par_cli->udp = make (udp_t) from (0)))
                goto new_failed;

            par_cli->cli     = va_arg(par, cli*)   ; if (!par_cli->cli)     goto new_failed;
            par_cli->pkt     = va_arg(par, dns_pkt); if (!par_cli->pkt)     goto new_failed;
            par_cli->pkt_box = va_arg(par, box*)   ; if (!par_cli->pkt_box) goto new_failed;
            par_cli->cli     = ref(par_cli->cli)   ;
            par_cli->res     = 0                   ;
            return true_t;
    new_failed:
            if (par_cli->pkt)     del(par_cli->pkt)    ;
            if (par_cli->pkt_box) del(par_cli->pkt_box);
            if (par_cli->cli)     del(par_cli->cli)    ;
            if (par_cli->udp)     del(par_cli->udp)    ;
            return false_t;
}

bool_t
    cli_res_clone
        (cli_res* par, cli_res* par_clone) {
            return false_t;
}

void
    cli_res_del
        (cli_res* par)       {
            del(par->pkt)    ;
            del(par->pkt_box);
            del(par->udp)    ;
            del(par->cli)    ;
}

bool_t  
    cli_res_next
        (cli_res* par)                          {
            if(!par->res)                       {
                par->res = dns_pkt_res(par->pkt);
                return par->res != 0;
            }

            par->res = dns_res_next(par->res);
            return par->res != 0;
}

str*    cli_res_req     (cli_res* par) { return dns_res_req (par->res); }
u16_t   cli_res_type    (cli_res* par) { return dns_res_type(par->res); }
u16_t   cli_res_cls     (cli_res* par) { return dns_res_cls (par->res); }
u32_t   cli_res_ttl     (cli_res* par) { return dns_res_ttl (par->res); }

str*    cli_res_as_a    (cli_res* par) { return dns_res_as_a    (par->res); }
str*    cli_res_as_cname(cli_res* par) { return dns_res_as_cname(par->res); }
str*    cli_res_as_ptr  (cli_res* par) { return dns_res_as_ptr  (par->res); }
dns_soa cli_res_as_soa  (cli_res* par) { return dns_res_as_soa  (par->res); }