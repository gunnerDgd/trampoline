add_executable       (example-query-query query/query.c)
target_link_libraries(example-query-query PRIVATE
    asterisk 
    asterisk-env 
    
    build 
    build-arch
    build-arch-asm

    ws2_32
    Mswsock

    trampoline
)