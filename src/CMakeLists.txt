
# INCLUDE_DIRECTORIES( . FenetrePrincipale module2 )
INCLUDE_DIRECTORIES( . )

MESSAGE( STATUS ${CMAKE_CURRENT_BINARY_DIR} )

SET( FENETRE_PRINCIPALE_SRC FenetrePrincipale/FenetrePrincipale.cpp FenetrePrincipale/module1_fichier2.cpp )
SET( MODULE2_SRC module2/module2_fichier1.cpp )

ADD_LIBRARY( src
             ${FENETRE_PRINCIPALE_SRC} ${MODULE2_SRC}
             resources/resource.qrc
           )

TARGET_LINK_LIBRARIES( src PUBLIC Qt6::Widgets )

ADD_EXECUTABLE( ${PROJECT_NAME}
                main.cpp )

TARGET_LINK_LIBRARIES( ${PROJECT_NAME} PRIVATE Qt6::Widgets Qt6::Core )
