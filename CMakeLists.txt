cmake_minimum_required(VERSION 3.13)
project(Stack VERSION 1.0 LANGUAGES CXX)

add_compile_options(
    -Werror
    -Wall
    -Wextra
)

if(NOT CMAKE_CXX_EXTENSIONS)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()

set(SOURCE_EXE tests/tests.cpp)
include_directories(include)
add_executable(test ${SOURCE_EXE})

# To add:
# cmake . -DSANITAIZER=ON
# cmake ---build .

if(NOT SANITAIZER)
    target_compile_options(test PRIVATE -fsanitize=address)
    target_link_options(test PRIVATE -fsanitize=address)
    target_compile_options(test PUBLIC -fsanitize=undefined)
    target_link_options(test PUBLIC -fsanitize=undefined)
endif()

set (CLANG_TIDY_FLAGS
     clang-tidy;
    -checks=*
    -header-filter=.;
    -warnings-as-errors=*;
    )

set_target_properties (test PROPERTIES CMAKE_CXX_CLANG_TIDY "{CLANG_TIDY_FLAGS}")
file (GLOB_RECURSE ALL_SOURCE_FILES tests/*.cpp include/*.h)

add_custom_target(
    clang_format
    COMMAND clang-clang_format
    -i
    tests/*.cpp include/*.h
)

target_link_libraries(test gtest pthread)