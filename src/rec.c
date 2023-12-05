#include "rec.h"
#include "zone.h"

#include "details/rec.h"
#include "details/zone.h"

#include <endian.h>
#include <string.h>

dns_rdata 
    dns_rdata_next
        (dns_rdata par)          {
            return list_next(par);
}

u16_t 
    dns_rdata_type
        (dns_rdata par)                            {
            if (!par)                      return 0; rdata* rec = list_get(par);
            if (!rec)                      return 0;
            if (trait_of(rec) != &rdata_t) return 0;

            return be16(rec->type);
}

u16_t 
    dns_rdata_cls
        (dns_rdata par)                            {
            if (!par)                      return 0; rdata* rec = list_get(par);
            if (!rec)                      return 0;
            if (trait_of(rec) != &rdata_t) return 0;

            return be16(rec->cls);
}

u32_t 
    dns_rdata_ttl
        (dns_rdata par)                            {
            if (!par)                      return 0; rdata* rec = list_get(par);
            if (!rec)                      return 0;
            if (trait_of(rec) != &rdata_t) return 0;

            return be32(rec->ttl);
}

u64_t 
    dns_rdata_pri
        (dns_rdata par)                            {
            if (!par)                      return 0; rdata* rec = list_get(par);
            if (!rec)                      return 0;
            if (trait_of(rec) != &rdata_t) return 0;

            return be16(rec->pri);
}

v4* 
    dns_rdata_as_a
        (dns_rdata par)                            {
            if (!par)                      return 0; rdata* rec = list_get(par);
            if (!rec)                      return 0;
            if (trait_of(rec) != &rdata_t) return 0;
            if (dns_rdata_type(par) != 1)  return 0;

            return &rec->a;
}

str* 
    dns_rdata_as_cname
        (dns_rdata par)                            {
            if (!par)                      return 0; rdata* rec = list_get(par);
            if (!rec)                      return 0;
            if (trait_of(rec) != &rdata_t) return 0;
            if (dns_rdata_type(par) != 5)  return 0;

            return &rec->cname;
}

str* 
    dns_rdata_as_ptr
        (dns_rdata par)                            {
            if (!par)                      return 0; rdata* rec = list_get(par);
            if (!rec)                      return 0;
            if (trait_of(rec) != &rdata_t) return 0;
            if (dns_rdata_type(par) != 12) return 0;

            return &rec->ptr;
}

str*
    dns_rec_name
        (dns_rec par)                            {
            if (!par)                    return 0; rec* rec = list_get(par);
            if (!rec)                    return 0;
            if (trait_of(rec) != &rec_t) return 0;

            return &rec->rec;
}

dns_rdata
    dns_rec_data
        (dns_rec par)                            {
            if (!par)                    return 0; rec* rec = list_get(par);
            if (!rec)                    return 0;
            if (trait_of(rec) != &rec_t) return 0;

            return list_begin(&rec->data);
}

dns_rdata 
    dns_rdata_a
        (dns_rec par, u32_t par_ttl, v4* par_a) {
            if (!par)                    return 0; rec* rec = list_get(par);
            if (!par_a)                  return 0;
            if (trait_of(par_a) != v4_t) return 0;
            if (!rec)                    return 0;
            if (trait_of(rec) != &rec_t) return 0;

            rdata* ret_data = make(&rdata_t) from (
                5      ,
                1      ,
                1      ,
                par_ttl,
                0      ,
                par_a
            );

            if (!ret_data) return false_t;
            dns_rdata ret = list_push_back(&rec->data, ret_data); del(ret_data);
            return    ret;
}

dns_rdata
    dns_rdata_a_str
        (dns_rec par, u32_t par_ttl, str* par_a)  {
            if (!par)                     return 0; rec* rec = list_get(par);
            if (!par_a)                   return 0;
            if (trait_of(par_a) != str_t) return 0;
            if (!rec)                     return 0;
            if (trait_of(rec) != &rec_t)  return 0;

            v4 ret_addr;
            if (!make_at(&ret_addr, v4_t) from(2, str_ptr(par_a), 0))
                return 0;

            dns_rdata ret = dns_rdata_a(par, par_ttl, &ret_addr); del(&ret_addr);
            return    ret;
}

dns_rdata
    dns_rdata_a_cstr
        (dns_rec par, u32_t par_ttl, const char* par_a) {
            if (!par)                     return 0; rec* rec = list_get(par);
            if (!par_a)                   return 0;
            if (!rec)                     return 0;
            if (trait_of(rec) != &rec_t)  return 0;

            v4 ret_addr;
            if (!make_at(&ret_addr, v4_t) from(2, par_a, 0))
                return 0;

            dns_rdata ret = dns_rdata_a(par, par_ttl, &ret_addr); del(&ret_addr);
            return    ret;
}

dns_rdata
    dns_rdata_cname
        (dns_rec par, u32_t par_ttl, str* par_a) {
            if (!par)                    return 0; rec* rec = list_get(par);
            if (!rec)                    return 0;
            if (trait_of(rec) != &rec_t) return 0;

            rdata* ret_data = make(&rdata_t) from (
                5      ,
                5      ,
                1      ,
                par_ttl,
                0      ,
                par_a
            );

            if (!ret_data) return false_t;
            dns_rdata ret = list_push_back(&rec->data, ret_data); del(ret_data);
            return    ret;
}

dns_rdata
    dns_rdata_cname_cstr
        (dns_rec par, u32_t par_ttl, const char* par_a)       {
            str ret_str                                       ; if (!make_at(&ret_str, str_t) from(0)) return 0;
            str_push_back_cstr(&ret_str, par_a, strlen(par_a));

            dns_rdata ret = dns_rdata_cname(par, par_ttl, &ret_str); del(&ret_str);
            return       ret;
}

dns_rdata
    dns_rdata_ptr
        (dns_rec par, u32_t par_ttl, str* par_a) {
            if (!par)                    return 0; rec* rec = list_get(par);
            if (!rec)                    return 0;
            if (trait_of(rec) != &rec_t) return 0;

            rdata* ret_data = make(&rdata_t) from (
                5      ,
                12     ,
                1      ,
                par_ttl, 
                0      ,
                par_a
            );

            if (!ret_data) return false_t;
            dns_rdata ret = list_push_back(&rec->data, ret_data); del(ret_data);
            return    ret;
}

dns_rdata
    dns_rdata_ptr_cstr
        (dns_rec par, u32_t par_ttl, const char* par_a)       {
            str ret_str                                       ; if (!make_at(&ret_str, str_t) from(0)) return 0;
            str_push_back_cstr(&ret_str, par_a, strlen(par_a));

            dns_rdata ret = dns_rdata_ptr(par, par_ttl, &ret_str); del(&ret_str);
            return    ret;
}