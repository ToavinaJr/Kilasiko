# Version minimum de CMake requise
cmake_minimum_required(VERSION 3.10)

# Nom du projet
project(CGIProject)

# Définir le standard C++ (ici C++11)
set(CMAKE_CXX_STANDARD 11)

# Inclure les fichiers d'en-tête
include_directories(include)

# Récupérer tous les fichiers .cpp dans le dossier source et ses sous-dossiers
file(GLOB_RECURSE SOURCES "source/*.cpp")

# Ajouter le fichier spécifique à chaque exécutable
set(LIST_USERS "cgi/source/listUsers.cpp")

# Ajouter un exécutable avec les fichiers trouvés + le fichier spécifique
add_executable(listUsers ${SOURCES} ${LIST_USERS})
add_executable(login ${SOURCES} ${SPECIFIC_SOURCE})
add_executable(registration ${SOURCES} ${SPECIFIC_SOURCE})

# Indiquer où les exécutables seront générés (dans le répertoire bin)
set_target_properties(listUsers PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set_target_properties(login PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set_target_properties(registration PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
