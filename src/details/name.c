#include "name.h"
#include "res.h"
#include "req.h"
#include "dns.h"

#include "endian.h"

obj_trait __dns_name_trait                  = {
    .init          = &__dns_name_init         ,
    .init_as_clone = &__dns_name_init_as_clone,
    .init_as_ref   =                         0,
    .deinit        = &__dns_name_deinit       ,
    .name          =                         0,
    .size          = &__dns_name_size 
};

bool_t 
    __dns_name_init
        (__dns_name* par_name, u32_t par_count, va_list par) {
            alloc* par_alloc = (par_count == 1) ? va_arg(par, alloc*) : get_alloc();
            if   (!par_alloc)
                return false_t;

            return make_at(par_name->name, str_t) from (1, par_alloc);
}

bool_t 
    __dns_name_init_as_clone
        (__dns_name* par, __dns_name* par_clone) {
            if(make_at(par->name, str_t) from (0))
                return false_t;

            str_push_back(&par->name, &par_clone->name);
            return true_t;
}

void  
    __dns_name_deinit
        (__dns_name* par)  {
            del(&par->name);
}

u64_t  
    __dns_name_size()            {
        return sizeof(__dns_name);
}

bool_t 
    __dns_name_from_str
        (__dns_name* par, str* par_str)                          {
            ptr  tok     = str_ptr           (par_str)           ,
                 tok_end = str_find_from_cstr(par_str, 0, ".", 1);
            u8_t len;

            if (null(tok) || null(tok_end))
                return false_t;

            while (!null(tok))                                                           {
                if (null(tok_end)) tok_end = ptr_seek(str_ptr(par_str), str_len(par_str));

                len     = ptr_dist(tok, tok_end)                 ;
                str_push_back_cstr(&par->name, &len, 1)          ;
                str_push_back_cstr(&par->name, ptr_raw(tok), len);

                tok     = ptr_seek          (tok_end, 1)                             ;
                tok_end = str_find_from_cstr(par_str, ptr_dist(tok, tok_end), ".", 1);
            }

            str_push_back_cstr(&par->name, "\0", 1);
            return true_t;
}

bool_t 
    __dns_name_from_ptr
        (__dns_name* par, ptr par_ptr, ptr par_dns) {
            u8_t  len;
            u16_t off;

            ptr_rd8(par_ptr, &len);
            while    (len)                                                                   {
                while(len & 0xC0)                                                            {
                    if (null(ptr_rd16(par_ptr, &off)))                         return false_t;
                    if (null(par_ptr = ptr_seek(par_ptr, be16(off) ^ 0xC000))) return false_t;

                    ptr_rd8(par_ptr, &len);
                }

                str_push_back_cstr(&par->name, &len            , 1)  ; if (null(par_ptr = ptr_seek(par_ptr, 1)))   return false_t;
                str_push_back_cstr(&par->name, ptr_raw(par_ptr), len); if (null(par_ptr = ptr_seek(par_ptr, len))) return false_t;
                
                if(null(ptr_rd8(par_ptr, &len))) return false_t;
            }

            str_push_back_cstr(&par->name, "\0", 1);
            return true_t;
}

str* 
    __dns_name_to_str
        (__dns_name* par)                 {
            u8_t len = 0                  ;
            ptr  ptr = str_ptr(&par->name);
            str* str = make(str_t) from(0);

            if (null(ptr = ptr_rd8(ptr, &len)))
                return false_t;
            while (len)                                   {
                str_push_back_cstr(str, ptr_raw(ptr), len);
                ptr = ptr_seek    (ptr,  len);
                ptr = ptr_rd8     (ptr, &len);
                
                if (null(ptr)) {
                    del(str)   ;
                    return 0   ;
                }
            }

            return str;
}

ptr
    __dns_name_to_ptr
        (__dns_name* par, ptr par_ptr, ptr par_dns)          {
            ptr  tok     =               str_ptr(&par->name) ,
                 tok_end = ptr_seek(tok, str_len(&par->name));
            u8_t len;

            if (null(tok) || null(tok_end))
                return ptr_null();

            while(!ptr_same(tok, tok_end))                                       {
                ptr off = ptr_find(par_dns, ptr_raw(tok), ptr_dist(tok, tok_end));
                if(!null(off))
                    return ptr_wr16(par_ptr, be16(ptr_dist(off, par_dns) | 0xC000));

                tok = ptr_rd8 (tok, &len); ptr_copy(par_ptr, tok, len);
                tok = ptr_seek(tok,  len);

                if (null(tok)) return ptr_null();
            }

            return ptr_wr8(par_ptr, 0);
}