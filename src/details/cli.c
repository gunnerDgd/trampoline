#include "cli.h"

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

void*
    cli_task_main
        (cli_task* par)                                     {
            if (await(par->task) != dns_pkt_size(par->pkt))
                goto main_failed;

            box *ret_box = make (box_t) from (1, 512);
            if (!ret_box)
                goto main_failed;
            if (!await(udp_recv(&par->cli->cli, box_ptr(ret_box), box_size(ret_box)))) {
                del(ret_box)    ;
                goto main_failed;
            }

            dns_pkt ret = make(dns_pkt_t) from(1, ret_box);
            if (dns_head_id(par->pkt) != dns_head_id(ret))
                goto main_failed_recv;
            
            del    (par->pkt);
            del    (par->cli);
            del    (ret_box) ;
            mem_del(0, par)  ;

            return ret;
    main_failed_recv:
            del    (ret)     ;
            del    (ret_box) ;
    main_failed:
            del    (par->pkt);
            del    (par->cli);
            mem_del(0, par)  ;
            
            return false_t;
}

bool_t 
    cli_new
        (cli* par_cli, u32_t par_count, va_list par)                       {
            if     (!make_at(&par_cli->cli, udp_t) from (0)) return false_t;
            switch (par_count)              {
            case 1:                         {
                v4  *addr = va_arg(par, v4*);
                if (!addr)                           goto new_failed;
                if (trait_of(addr) != v4_t)          goto new_failed;
                if (!clone_at(&par_cli->addr, addr)) goto new_failed;
                break;
            }
            case 2:                                        {
                const char* addr = va_arg(par, const char*);
                u16_t       port = va_arg(par, u16_t)      ;

                if (!make_at(&par_cli->addr, v4_t) from(2, addr, port))
                    return false_t;
                break;
            }
            default:
                goto new_failed;
            }

            dns_flag pkt_flag = { .rd = 1 };
            box     *pkt_box  = make(box_t)     from (1, 512)                 ; if (!pkt_box) goto new_failed;
            par_cli->pkt      = make(dns_pkt_t) from (3, pkt_box, 1, pkt_flag);
            if (!par_cli->pkt) {
                del(pkt_box)   ;
                goto new_failed;
            }

            del(pkt_box) ;
            return true_t;
    new_failed:
            del(&par_cli->cli);
            return false_t    ;

}
bool_t 
    cli_clone
        (cli* par, cli* par_clone) { 
            return false_t; 
}

void
    cli_del(cli* par)  { 
        del(&par->cli) ;
        del(&par->addr);
}

task   
    cli_req
        (cli* par)                                    {
            if (!par->pkt)                    return 0;
            if (dns_req_count(par->pkt) == 0) return 0;
            if (dns_res_count(par->pkt))      return 0;

            cli_task *ret = mem_new(0, sizeof(cli_task)); if (!ret) return 0;
            ret->cli  = ref (par)     ;
            ret->pkt  = par->pkt      ;
            ret->task = udp_send_to   (
                &par->cli             ,
                dns_pkt_ptr (ret->pkt),
                dns_pkt_size(ret->pkt),
                &par->addr
            );

            if (!ret->task) goto req_failed;

            dns_flag pkt_flag = { .rd = 1 };
            box     *pkt_box  = make(box_t)     from (1, 512)                 ; if (!pkt_box) return 0;
            par->    pkt      = make(dns_pkt_t) from (3, pkt_box, 1, pkt_flag); del (pkt_box);

            return async(cli_task_main, ret);
    req_failed:
            del(ret->cli);
            del(ret->pkt);
            del(ret)    ;

            return 0;
}