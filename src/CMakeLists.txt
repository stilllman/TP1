
# INCLUDE_DIRECTORIES( . FenetrePrincipale module2 )
# J'aurais plutôt fait des target_include_directories mais ça se discute.
INCLUDE_DIRECTORIES( . )

MESSAGE( STATUS ${CMAKE_CURRENT_BINARY_DIR} ) # bizarre comme message ?

# Les variables avec des listes de sources c'est très old school, la façon moderne c'est de faire
# d'abord ton add_library ou add_executable et ensuite d'utiliser un ou plusieurs target_sources().
SET( TP1_CPP_SRC tp1_cpp/Vegetal.cpp tp1_cpp/Arbre.cpp tp1_cpp/Fleur.cpp tp1_cpp/Champignon.cpp )
SET( FENETRE_PRINCIPALE_SRC FenetrePrincipale/FenetrePrincipale.cpp FenetrePrincipale/module1_fichier2.cpp )
SET( MODULE2_SRC module2/module2_fichier1.cpp )

ADD_LIBRARY( src # bizarre comme nom de librairie, ça porte un peu à confusion je trouve
             ${TP1_CPP_SRC}
             ${FENETRE_PRINCIPALE_SRC} ${MODULE2_SRC}
             resources/resource.qrc
           )

TARGET_LINK_LIBRARIES( src PUBLIC Qt6::Widgets )

ADD_EXECUTABLE( ${PROJECT_NAME}
                main.cpp )

TARGET_LINK_LIBRARIES( ${PROJECT_NAME} PRIVATE Qt6::Widgets Qt6::Core )
