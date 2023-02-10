cmake_minimum_required(VERSION 3.8)
project(nada_sfml)
set(CMAKE_CXX_STANDARD 17)

set(LIBNADA_SFML_INCLUDE_DIRS ${CMAKE_CURRENT_LIST_DIR}/include)
set(LIBNADA_SFML_INCLUDE_DIRS ${LIBNADA_SFML_INCLUDE_DIRS} PARENT_SCOPE)
file(GLOB_RECURSE CPP_FILES src/*.cpp)

# libnada_sfml
# REQUIRES libwebp-dev libsfml-dev
add_library(nada_sfml STATIC ${CPP_FILES} src/thirdparty/gifdec.c)
target_include_directories(nada_sfml PRIVATE ${LIBNADA_SFML_INCLUDE_DIRS})
target_link_libraries(nada_sfml PRIVATE sfml-system sfml-window sfml-graphics pthread webp)

# libnada_sfml - tests
add_executable(nada_sfml_test test/tests.cpp)
target_include_directories(nada_sfml_test PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)
target_include_directories(nada_sfml_test PRIVATE ${CMAKE_CURRENT_LIST_DIR}/test/doctest)
target_link_libraries(nada_sfml_test PRIVATE nada_sfml pthread gcov webp)
target_compile_options(nada_sfml_test PRIVATE -coverage)
