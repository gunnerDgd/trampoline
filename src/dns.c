#include "dns.h"
#include "details/dns.h"

#include "endian.h"

obj* 
    dns_new(ptr par, u16_t par_id, dns_flag par_flag)      {
        if(null(par))                              return 0;
        dns* ret = make(&dns_t) from(0); if (!ret) return 0;

        ret->ptr     = par;
        ret->ptr_off = par;
        
        if (!make_at(ret->dns_head, &dns_head_t) from(3, ret, par_id, par_flag.flag)) {
            del(ret);
            return 0;
        }

        return ret;
}

obj* 
    dns_new_from(ptr par)                                  {
        if(null(par))                              return 0;
        dns* ret = make(&dns_t) from(0); if (!ret) return 0;

        ret->ptr     = par;
        ret->ptr_off = par;

        if (!make_at(ret->dns_head, &dns_head_t) from(1, ret))
            return false_t;

        u16_t cnt_req        = be16(ret->dns_head.form->req)       ,
              cnt_res        = be16(ret->dns_head.form->res)       ,
              cnt_auth       = be16(ret->dns_head.form->auth)      ,
              cnt_additional = be16(ret->dns_head.form->additional);

        while (cnt_req--)                               {
            dns_req* req = make(&dns_req_t) from(1, ret);
            if (!req)   {
                del(ret);
                return 0;
            }

            list_push_back(&ret->req, req);
            del(req);
        }

        while (cnt_res--)                               {
            dns_res* res = make(&dns_res_t) from(1, ret);
            if (!res)   {
                del(ret);
                return 0;
            }

            list_push_back(&ret->res, res);
            del(res);
        }

        return ret;
}

u16_t
    dns_head_id(obj* par)                    {
        if (!par)                    return 0;
        if (trait_of(par) != &dns_t) return 0;

        return be16(((dns*)par)->dns_head.form->id);
}

dns_flag 
    dns_head_flag(obj* par)         {
        dns_flag ret = { .flag = 0 };

        if (!par)                    return ret;
        if (trait_of(par) != &dns_t) return ret;

        ret.flag = be16(((dns*)par)->dns_head.form->flag);
        return ret;
}

u64_t 
    dns_len(obj* par)                        {
        if (!par)                    return 0;
        if (trait_of(par) != &dns_t) return 0;

        return ptr_dist(((dns*)par)->ptr, ((dns*)par)->ptr_off);
}

it    
    dns_req_begin(obj* par)                       {
        if (!par)                    return npos();
        if (trait_of(par) != &dns_t) return npos();

        return list_begin(&((dns*)par)->req);
}

it    
    dns_req_end(obj* par)                         {
        if (!par)                    return npos();
        if (trait_of(par) != &dns_t) return npos();

        return list_end(&((dns*)par)->req);
}

u16_t 
    dns_req_count(obj* par)                            {
            if (!par)                    return false_t;
            if (trait_of(par) != &dns_t) return false_t;

            return be16(((dns*)par)->dns_head.form->req);
}

it    
    dns_res_begin(obj* par)                                    {
        if (!par)                    return npos();
        if (trait_of(par) != &dns_t) return npos();

        return list_begin(&((dns*)par)->res);
}

it    
    dns_res_end(obj* par)                         {
        if (!par)                    return npos();
        if (trait_of(par) != &dns_t) return npos();

        return list_end(&((dns*)par)->res);
}

u16_t 
    dns_res_count(obj* par)                        {
        if (!par)                    return false_t;
        if (trait_of(par) != &dns_t) return false_t;

        return be16(((dns*)par)->dns_head.form->res);
}