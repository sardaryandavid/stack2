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

#set(SOURCE_LIB src/Stack.cpp)
set(SOURCE_EXE tests/tests.cpp)

add_executable(test ${SOURCE_EXE})
#add_library(Stack STATIC ${SOURCE_LIB})

# To add:
# cmake . -DSANITAIZER=ON
# cmake ---build .
if(NOT SANITAIZER)
    target_compile_options(test PRIVATE -fsanitize=address)
    target_link_options(test PRIVATE -fsanitize=address)
    target_compile_options(test PUBLIC -fsanitize=undefined)
    target_link_options(test PUBLIC -fsanitize=undefined)
endif()

target_link_libraries(test gtest pthread)
