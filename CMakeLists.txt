cmake_minimum_required(VERSION 3.13)
project(my_lang)

set(CMAKE_CXX_STANDARD 17)

find_package(LLVM REQUIRED CONFIG)

include_directories(include)
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

add_executable(my_lang
    src/main.cpp
    src/lexer.cpp
    src/parser.cpp
    src/ast.cpp
    src/codegen.cpp
)

llvm_map_components_to_libnames(llvm_libs support core irreader nativecodegen)

target_link_libraries(my_lang PRIVATE ${llvm_libs})
