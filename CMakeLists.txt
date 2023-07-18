cmake_minimum_required(VERSION 3.5)

project(2B3Chromie LANGUAGES C)

add_subdirectory(lib2B3Chromie)

set(SRCS
    main.c
   
)

set(HEADERS
    main.h
    )

add_executable(2B3Chromie ${SRCS} ${HEADERS})
target_link_libraries(2B3Chromie lib2B3Chromie)

install(TARGETS 2B3Chromie
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
