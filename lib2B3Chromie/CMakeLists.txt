cmake_minimum_required(VERSION 3.5)

project(2B3ChromieCore)
# Crée des variables avec les fichiers à compiler
set(SRCS
    memoire.c
    conversion.c
    couleurs.c
    recherche.c
    gestion_bibliotheque.c
    papiers.c
    )
    
set(HEADERS
    memoire.h
    structures.h
    conversion.h
    couleurs.h
    recherche.h
    gestion_bibliotheque.h
    papiers.h
    stb_image/stb_image.h
    stb_image/stb_image_write.h

    )


add_library(2B3ChromieCore ${SRCS} ${HEADERS})
target_link_libraries(2B3ChromieCore m)
target_include_directories(2B3ChromieCore PUBLIC .)
