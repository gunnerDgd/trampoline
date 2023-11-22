#include "name.h"
#include "details/name.h"

obj* 
	dns_name_new
		(str* par)									 {
			dns_name* ret = make(&dns_name_t) from(0);
			if (!ret)				         return 0;
			if (!dns_name_from_str(ret, par)) {
				del(ret);
				return 0;
			}

			return ret;
}

obj* 
	dns_name_new_cstr
		(const char* par, u64_t par_len)		   {
			str *ret_str = make(str_t) from(0); 
			if (!ret_str) return 0;

			dns_name *ret = make(&dns_name_t) from(0);
			if (!ret)	    {
				del(ret_str);
				return 0;
			}

			str_push_back_cstr    (ret_str, par, par_len);
			if (!dns_name_from_str(ret, ret_str))		 {
				del(ret_str);
				del(ret)    ;
				return     0;
			}

			return ret;
}

str* 
	dns_name_as_str
		(obj* par)									 {
			if(!par)						 return 0;
			if(trait_of(par) != &dns_name_t) return 0;

			return dns_name_to_str(par);
}