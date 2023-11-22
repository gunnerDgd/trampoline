project    (trampoline)
add_library(trampoline STATIC
    details/name.h
    details/name.c

    details/head.h
    details/head.c

    details/req.h
    details/req.c

    details/res.h
    details/res.c

    details/dns.h
    details/dns.c

    name.h
    name.c

    req.h
    req.c

    res.h
    res.c

    dns.h
    dns.c

    dns/a.h
    dns/a.c

    dns/cname.h
    dns/cname.c
)