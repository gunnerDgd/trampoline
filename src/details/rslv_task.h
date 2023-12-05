#ifndef __DETAILS_RSLV_TASK_H__
#define __DETAILS_RSLV_TASK_H__

#include <obj.h>
#include <udp.h>
#include <async.h>
#include <v4.h>

#include "../pkt.h"
#include "../req.h"
#include "../res.h"
#include "../rec.h"

extern obj_trait rslv_task_t;
typedef struct   rslv_task  {
    obj          head;
    struct rslv *rslv;
    dns_req      req ;
    dns_pkt      pkt ;
    udp         *cli ;
    v4          *addr;
}   rslv_task;

void*   rslv_task_main      (rslv_task*);
bool_t  rslv_task_new       (rslv_task*, u32_t, va_list);
bool_t  rslv_task_clone     (rslv_task*, rslv_task*)    ;
void    rslv_task_del       (rslv_task*)                ;

task    rslv_res            (rslv_task*)                             ;
str*    rslv_req_name       (rslv_task*)                             ;
u16_t   rslv_req_type       (rslv_task*)                             ;
u16_t   rslv_req_cls        (rslv_task*)                             ;
dns_req rslv_req_next       (rslv_task*)                             ;

void    rslv_rec            (rslv_task*, dns_rec)           ;
dns_res rslv_a              (rslv_task*, u32_t, v4*)        ;
dns_res rslv_a_str          (rslv_task*, u32_t, str*)       ;
dns_res rslv_a_cstr         (rslv_task*, u32_t, const char*);

dns_res rslv_cname          (rslv_task*, u32_t, str*)       ;
dns_res rslv_cname_cstr     (rslv_task*, u32_t, const char*);

dns_res rslv_soa            (rslv_task*, u32_t, dns_soa)    ;
dns_res rslv_ptr            (rslv_task*, u32_t, str*)       ;
dns_res rslv_ptr_cstr       (rslv_task*, u32_t, const char*);

dns_res rslv_auth_a         (rslv_task*, u32_t, v4*)        ;
dns_res rslv_auth_a_str     (rslv_task*, u32_t, str*)       ;
dns_res rslv_auth_a_cstr    (rslv_task*, u32_t, const char*);

dns_res rslv_auth_cname     (rslv_task*, u32_t, str*)       ;
dns_res rslv_auth_cname_cstr(rslv_task*, u32_t, const char*);

dns_res rslv_auth_soa       (rslv_task*, u32_t, dns_soa)    ;
dns_res rslv_auth_ptr       (rslv_task*, u32_t, str*)       ;
dns_res rslv_auth_ptr_cstr  (rslv_task*, u32_t, const char*);

#endif