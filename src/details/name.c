#include "name.h"
#include "dns.h"

#include <stdio.h>

obj_trait __dns_name_trait                  = {
    .init          = &__dns_name_init         ,
    .init_as_clone = &__dns_name_init_as_clone,
    .init_as_ref   =                         0,
    .deinit        = &__dns_name_deinit       ,
    .name          = &__dns_name_str          ,
    .size          = &__dns_name_size
};

bool_t
    __dns_name_init
        (__dns_name* par_name, u32_t par_count, va_list par) {
            par_name->dns = ref(va_arg(par, __dns*));
            par_name->len = 0;

            if (!make_at(par_name->name, str_t) from(0)) {
                del(par_name->dns);
                return false_t    ;
            }

            par_name->name_ptr = par_name->dns->ptr_off ;
            if (par_count == 1)                         {
                par_name->len = __dns_name_len(par_name);
                return true_t;
            }

            str_push_back(&par_name->name, va_arg(par, str*))             ;
            ptr   tok     = str_ptr           (&par_name->name)           ,
                  tok_end = str_find_from_cstr(&par_name->name, 0, ".", 1);
            u64_t len     = 0;

            while (!ptr_same(tok_end, ptr_null()))                                               {
                ptr off_comp = ptr_find(par_name->dns->ptr, ptr_raw(tok), ptr_dist(tok, tok_end));
                if(!ptr_same(off_comp, ptr_null())) {
                    ptr_wr16(par_name->dns->ptr_off, (0b11000000 << 8) | (ptr_dist(off_comp, par_name->dns->ptr) - 1));
                    
                    par_name->dns->ptr_off  = ptr_seek(par_name->dns->ptr_off, 2);
                    par_name->len          += 2;

                    goto while_next;
                }

                len = ptr_dist(tok, tok_end);

                ptr_wr8  (par_name->dns->ptr_off, len)              ; par_name->dns->ptr_off = ptr_seek(par_name->dns->ptr_off, 1)  ;
                ptr_write(par_name->dns->ptr_off, ptr_raw(tok), len); par_name->dns->ptr_off = ptr_seek(par_name->dns->ptr_off, len);
                par_name->len += (len + 1)       ;
            while_next:
                tok     = ptr_seek(tok_end, 1);
                tok_end = str_find_from_cstr               (
                    &par_name->name                        ,
                    ptr_dist(str_ptr(&par_name->name), tok),
                    "."                                    ,
                    1
                );
            }

            len = str_len(&par_name->name) - ptr_dist(str_ptr(&par_name->name), tok);

            ptr_wr8  (par_name->dns->ptr_off, len)              ; par_name->dns->ptr_off = ptr_seek(par_name->dns->ptr_off, 1)  ;
            ptr_write(par_name->dns->ptr_off, ptr_raw(tok), len); par_name->dns->ptr_off = ptr_seek(par_name->dns->ptr_off, len);

            par_name->len += (len + 2)         ;
            ptr_wr8 (par_name->dns->ptr_off, 0); par_name->dns->ptr_off = ptr_seek(par_name->dns->ptr_off, 1);
            return true_t                      ;
}

bool_t
    __dns_name_init_as_clone
        (__dns_name* par, __dns_name* par_clone) {
            return false_t;
}

void   
    __dns_name_deinit
        (__dns_name* par)  {
            del(par->dns)  ;
            del(&par->name);
}

u64_t  
    __dns_name_size()            {
        return sizeof(__dns_name);
}

str* 
    __dns_name_str
        (__dns_name* par)             {
            if(!str_empty(&par->name))
                return &par->name;

            u16_t   len = 0            ;
            ptr     tok = par->name_ptr;
            ptr_rd8(tok, &len)         ;

            while (len && !ptr_same(tok, ptr_null()))                          {
                if(len & (0xC0))                                               {
                    ptr pos;
                    while(len & (0xC0))                                        {
                        ptr_rd16(tok, &len); pos = ptr_seek(par->dns->ptr, len);
                        ptr_rd8 (pos, &len);
                    }
                    pos = ptr_seek(pos, 1);

                    str_push_back_cstr(&par->name, ptr_raw(pos), len);
                    str_push_back_cstr(&par->name, ".", 1)           ;

                    tok = ptr_seek(tok, 2);
                    ptr_rd8(tok, &len)    ;
                    continue              ;
                }
                tok = ptr_seek(tok, 1);

                str_push_back_cstr(&par->name, ptr_raw(tok), len);
                str_push_back_cstr(&par->name, ".", 1)           ;

                tok = ptr_seek(tok, len);
                ptr_rd8(tok, &len)      ;
            }

            return &par->name;
}

u64_t
    __dns_name_len
        (__dns_name* par)               {
            if(par->len) return par->len;

            u16_t   len                  = 0;
            ptr_rd8(par->dns->ptr_off, &len);
            while  (len && !ptr_same(par->dns->ptr_off, ptr_null()))  {
                if (len & (0xC0))                                     {
                    par->len += 2                                     ;
                    par->dns->ptr_off = ptr_seek(par->dns->ptr_off, 2);

                    return par->len;
                }

                par->len         +=                            (len + 1);
                par->dns->ptr_off = ptr_seek(par->dns->ptr_off, len + 1);

                ptr_rd8(par->dns->ptr_off, &len);
            }

            par->dns->ptr_off = ptr_seek(par->dns->ptr_off, 1);
            return par->len + 1;
}