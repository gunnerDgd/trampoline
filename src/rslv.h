#ifndef __RSLV_H__
#define __RSLV_H__

#include <obj.h>
#include <task.h>

#include "req.h"
#include "res.h"
#include "soa.h"

extern obj_trait* dns_rslv_t   ;
typedef obj*      dns_rslv     ;
typedef void*     dns_rslv_task;

dns_rslv_task dns_rslv_run            (dns_rslv)                                  ;
task          dns_rslv_res            (dns_rslv_task)                             ;
str*          dns_rslv_req_name       (dns_rslv_task)                             ;
u16_t         dns_rslv_req_type       (dns_rslv_task)                             ;
u16_t         dns_rslv_req_cls        (dns_rslv_task)                             ;
bool_t        dns_rslv_next           (dns_rslv_task)                             ;

dns_res       dns_rslv_a              (dns_rslv_task, u32_t, v4*)        ;
dns_res       dns_rslv_a_str          (dns_rslv_task, u32_t, str*)       ;
dns_res       dns_rslv_a_cstr         (dns_rslv_task, u32_t, const char*);

dns_res       dns_rslv_cname          (dns_rslv_task, u32_t, str*)       ;
dns_res       dns_rslv_cname_cstr     (dns_rslv_task, u32_t, const char*);

dns_res       dns_rslv_soa            (dns_rslv_task, u32_t, dns_soa)    ;
dns_res       dns_rslv_ptr            (dns_rslv_task, u32_t, str*)       ;
dns_res       dns_rslv_ptr_cstr       (dns_rslv_task, u32_t, const char*);

dns_res       dns_rslv_auth_a         (dns_rslv_task, u32_t, v4*)        ;
dns_res       dns_rslv_auth_a_str     (dns_rslv_task, u32_t, str*)       ;
dns_res       dns_rslv_auth_a_cstr    (dns_rslv_task, const char*);

dns_res       dns_rslv_auth_cname     (dns_rslv_task, u32_t, str*)       ;
dns_res       dns_rslv_auth_cname_cstr(dns_rslv_task, u32_t, const char*);

dns_res       dns_rslv_auth_soa       (dns_rslv_task, u32_t, dns_soa)    ;
dns_res       dns_rslv_auth_ptr       (dns_rslv_task, u32_t, str*)       ;
dns_res       dns_rslv_auth_ptr_cstr  (dns_rslv_task, u32_t, const char*);


#endif