# to launch: 
# cd build
# cmake ..
# cmake --build . config Release

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

set(SOURCE_EXE ../tests/tests.cpp)
set(INCLUDE ../include)
include_directories(include)
add_executable(test ${SOURCE_EXE})
set(TEST test)
target_link_libraries(${TEST} gtest pthread)

# To add:
# cmake -DADD_SANITAIZER=ON ..
# cmake --build .
# make clang_format

if(ADD_SANITAIZER)
    message ("Build with sanitaizers")
    target_compile_options(${TEST} PRIVATE -fsanitize=address)
    target_link_options(${TEST} PRIVATE -fsanitize=address)
    target_compile_options(${TEST} PUBLIC -fsanitize=undefined)
    target_link_options(${TEST} PUBLIC -fsanitize=undefined)
endif()

if(ADD_CLANG_TIDY)
    message ("Build with clang-tidy")
    # set (CLANG_TIDY_FLAGS
    #      clang-tidy;
    #      -checks=*;
    #      -header-filter=.;
    #      -warnings-as-errors=*;
    #     )

    # set_target_properties (${TEST} PROPERTIES CXX_CLANG_TIDY "{CLANG_TIDY_FLAGS}")
    add_custom_target (
                clang_tidy
                COMMAND clang-tidy -warnings-as-errors=* ${SOURCE_EXE} -- -DDEBUG -I${INCLUDE}
                )
endif()

if(ADD_CLANG_FORMAT)
    message ("Build with clang-format")
    file (GLOB_RECURSE ALL_SOURCE_FILES tests/*.cpp include/*.h)
    add_custom_target(
        clang_format
        COMMAND clang-format
        -style=file
        -i
        ${ALL_SOURCE_FILES}
    )
endif()