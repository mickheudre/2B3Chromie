cmake_minimum_required(VERSION 3.5)

project(2B3Chromie LANGUAGES C)

set(SRCS
    main.c
    conversion.c
    couleurs.c
    recherche.c
    gestion_bibliotheque.c
    papiers.c
)

set(HEADERS
    main.h
    structures.h
    conversion.h
    couleurs.h
    recherche.h
    gestion_bibliotheque.h
    papiers.h
    stb_image/stb_image.h
    stb_image/stb_image_write.h

    )

add_executable(2B3Chromie ${SRCS} ${HEADERS})
target_link_libraries(2B3Chromie m)
set(CMAKE_CXX_FLAGS "-O3")

install(TARGETS 2B3Chromie
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
