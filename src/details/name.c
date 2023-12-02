#include "name.h"
#include "res.h"
#include "req.h"
#include "dns.h"

#include "endian.h"

obj_trait name_t         = {
    .on_new   = &name_new  ,
    .on_clone = &name_clone,
    .on_ref   =           0,
    .on_del   = &name_del  ,
    .size     = sizeof(name)
};

bool_t 
    name_new
        (name* par_name, u32_t par_count, va_list par)   {
            if (!make_at(&par_name->name, str_t) from(0)) return false_t;
            if (par_count == 1)                           return name_new_from_str(par_name, va_arg(par, str*));
            if (par_count == 2)                       {
                dns  *par_pkt     = va_arg(par, dns*) ;
                u8_t *par_pkt_ptr = va_arg(par, u8_t*);

                if (!par_pkt)                                              return false_t;
                if (!par_pkt_ptr)                                          return false_t;
                if ((par_pkt_ptr - par_pkt->ptr) > box_size(par_pkt->box)) return false_t;

                return name_new_from_pkt(par_name, par_pkt, par_pkt_ptr);
            }

            return false_t;
}

bool_t 
    name_clone
        (name* par, name* par_clone)               {
            if(make_at(&par->name, str_t) from (0)) return false_t;

            str_push_back(&par->name, &par_clone->name);
            return true_t;
}

void  
    name_del
        (name* par)  {
            del(&par->name);
}

bool_t 
    name_new_from_str
        (name* par, str* par_str)                                       {
            u8_t *str =              str_ptr      (par_str)             ;
            u64_t tok = 0, tok_pos = str_find_cstr(par_str, tok, ".", 1),
                  len = 0;
            
            if    (tok_pos == -1) return false_t;
            while (tok_pos != -1)                             {
                len = tok_pos - tok                           ;
                str_push_back_cstr(&par->name, &len     , 1)  ;
                str_push_back_cstr(&par->name, str + tok, len);

                tok     = tok_pos + 1;
                tok_pos = str_find_cstr(par_str, tok, ".", 1);
            }

            len = str_len(par_str) - tok                  ;
            str_push_back_cstr(&par->name, &len     , 1)  ;
            str_push_back_cstr(&par->name, str + tok, len);
            str_push_back_cstr(&par->name, "\0"     , 1)  ;
            return true_t;
}

bool_t
    name_new_from_pkt
        (name* par, struct dns* par_pkt, u8_t* par_ptr) {
            u8_t  len;
            u16_t off;

            if (par_ptr < par_pkt->ptr)                            return false_t;
            if (par_ptr > (par_pkt->ptr + box_size(par_pkt->box))) return false_t;

            len = *par_ptr;
            while    (len)                        {
                while(len & 0xC0)                 {
                    off      = *(u16_t*)par_ptr   ;
                    off      = be16(off) ^ 0xC000 ;
                    par_ptr  =  par_pkt->ptr + off; if (par_ptr > (par_pkt->ptr + box_size(par_pkt->box))) return false_t;
                    len      = *par_ptr           ;
                }

                if ((par_ptr + len) > (par_pkt->ptr + box_size(par_pkt->box)))
                    return false_t;

                str_push_back_cstr(&par->name, &len   , 1)  ; par_ptr += 1  ;
                str_push_back_cstr(&par->name, par_ptr, len); par_ptr += len;

                len = *par_ptr;
            }

            str_push_back_cstr(&par->name, "\0", 1);
            return true_t;
}

str* 
    name_as_str
        (name* par)                           {
            str    *ret = make(str_t) from (0); if (!ret) return 0;
            u64_t   len                       ;
            u8_t   *ptr = str_ptr(&par->name) ;
            while (*ptr)                      {
                len = *ptr                       ; ptr++     ;
                str_push_back_cstr(ret, ptr, len); ptr += len;
                str_push_back_cstr(ret, "." , 1) ;
            }
            str_pop_back      (ret, 1)      ;
            str_push_back_cstr(ret, "\0", 1);
            return ret;
}

u64_t       name_len(name* par) { return str_len(&par->name); }
const char* name_ptr(name* par) { return str_ptr(&par->name); }