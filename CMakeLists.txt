# Les noms de fonction en majuscule c'est très très très vieux et déconseillé par tout le monde
# (cmake y compris).
CMAKE_MINIMUM_REQUIRED( VERSION 3.16 )

PROJECT( TestCompil VERSION 1.0.0 )
MESSAGE( STATUS "**** Configuring ${PROJECT_NAME} version ${PROJECT_VERSION} ****")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Werror -Wno-deprecated) # Je ferais plutôt comme ça perso.
SET( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wno-unused -Wno-uninitialized" ) # T'as du code C ?

# PROJECT_BINARY_BIR ça permet d'éviter d'avoir à tout renommer si tu changes le nom du projet (et
# ça se copie/colle mieux).
# Si tu utilises CMAKE_BUILD_TYPE ton projet ne fonctionne plus correctement avec un générateur
# multiconfig. D'autant qu'en single-config le binary dir est déjà spécifique à une config
# particulière (tu es dans build_debug) donc ça ne sert pas à grand chose de le remettre. En
# multiconfig, le répertoire config sera ajouté automatiquement par cmake.
# EXECUTABLE_OUTPUT_PATH c'est legacy, ils conseillent plutôt CMAKE_RUNTIME_OUTPUT_DIRECTORY (et
# CMAKE_LIBRARY_OUTPUT) maintenant.
SET( EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE} )
SET( LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE} )

SET( CMAKE_AUTOMOC ON )
SET( CMAKE_AUTORCC ON )
FIND_PACKAGE( Qt6 REQUIRED COMPONENTS Core Widgets )

enable_testing()

ADD_SUBDIRECTORY( src )
ADD_SUBDIRECTORY( test_unit )
