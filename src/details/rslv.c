#include "rslv.h"

obj_trait rslv_t          = {
    .on_new   = &rslv_new   ,
    .on_clone = &rslv_clone ,
    .on_del   = &rslv_del   ,
    .on_ref   = 0           ,
    .size     = sizeof(rslv)
};

rslv_req* 
    rslv_run_main
        (rslv* par)                                            {
            v4  *udp_addr = make (v4_t)  from (2, "0.0.0.0", 0);
            udp *udp      = make (udp_t) from (0)              ;
            box *box      = make (box_t) from (1, 512)         ;

            if (!udp_addr) goto run_failed;
            if (!udp)      goto run_failed;
            if (!box)      goto run_failed;
                        
            if (!udp_conn(udp, &par->addr))                                        goto run_failed;
            if (!await(udp_recv_from(udp, box_ptr(box), box_size(box), udp_addr))) goto run_failed;
            
            dns_pkt pkt = make (dns_pkt_t) from (1, box);
            if    (!pkt) goto run_failed;

            del(box);
            return make (&rslv_req_t) from (
                4       ,
                par     ,
                pkt     ,
                udp     ,
                udp_addr
            );
    run_failed:
            if (box)      del(box)     ;
            if (udp_addr) del(udp_addr);
            if (udp)      del(udp)     ;
            
            del(par);
            return 0;
}

bool_t 
    rslv_new
        (rslv* par_rslv, u32_t par_count, va_list par) {
            switch(par_count)              {
            case 1:                        {
                v4  *addr = va_arg(par, v4*);
                if (!addr)                            return false_t;
                if (trait_of(addr) != v4_t)           return false_t;
                if (!clone_at(&par_rslv->addr, addr)) return false_t;

                break;
            }

            case 2:                                        {
                const char* addr = va_arg(par, const char*);
                u16_t       port = va_arg(par, u16_t)      ;
                if (!make_at(&par_rslv->addr, v4_t) from(2, addr, port))
                    return false_t;

                break;
            }    
            }

            return true_t;
}

bool_t 
    rslv_clone
        (rslv* par, rslv* par_clone) { 
            return false_t; 
}

void
    rslv_del
        (rslv* par)        { 
            del(&par->addr);
}

task 
    rslv_run
        (rslv* par)                            {
            return async(rslv_run_main, ref(par));
}