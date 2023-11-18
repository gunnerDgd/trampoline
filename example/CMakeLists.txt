add_executable       (example-query-query query/query.c)
target_link_libraries(example-query-query PRIVATE
    asterisk 
    asterisk-env 
    
    build 
    build-arch
    build-arch-asm
    build-preset 

    ws2_32
    Mswsock

    trampoline
)