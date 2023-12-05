add_executable       (example-cli-cli cli/cli.c)
target_link_libraries(example-cli-cli PRIVATE
    asterisk 
    asterisk-env 
    
    build 
    build-arch
    build-arch-asm

    ws2_32
    Mswsock

    trampoline
)

add_executable       (example-rslv-rslv rslv/rslv.c)
target_link_libraries(example-rslv-rslv PRIVATE
    asterisk 
    asterisk-env 
    
    build 
    build-arch
    build-arch-asm

    ws2_32
    Mswsock

    trampoline
)

add_executable       (example-ns-ns ns/ns.c)
target_link_libraries(example-ns-ns PRIVATE
    asterisk 
    asterisk-env 
    
    build 
    build-arch
    build-arch-asm

    ws2_32
    Mswsock

    trampoline
)