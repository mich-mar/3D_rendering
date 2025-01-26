cmake_minimum_required(VERSION 3.10)

# Nazwa projektu
project(3D_rendering)

# Ustaw standard C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Dodaj flagi kompilatora dla lepszej diagnostyki błędów
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    # Włącz ostrzeżenia na maksymalnym poziomie
    add_compile_options(-Wall -Wextra -pedantic)
    # Włącz ostrzeżenia o nieużywanych zmiennych i funkcjach
    add_compile_options(-Wunused-variable -Wunused-function)
    # Ustawienie włączonych ostrzeżeń w trybie debug
    add_compile_options(-g)
elseif(MSVC)
    # Włączenie ostrzeżeń w Visual Studio
    add_compile_options(/W4 /WX)  # /W4 = warning level 4, /WX = treat warnings as errors
endif()

# Dodanie wszystkich plików źródłowych z katalogu src/
file(GLOB_RECURSE SOURCES src/*.cpp)

# Dodanie katalogu z plikami nagłówkowymi
include_directories(lib/)

# Tworzenie pliku wykonywalnego
add_executable(${PROJECT_NAME} ${SOURCES})

# Znajdź SFML
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

# Połącz projekt z bibliotekami SFML
target_link_libraries(${PROJECT_NAME} sfml-system sfml-window sfml-graphics sfml-audio)
