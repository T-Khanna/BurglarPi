cmake_minimum_required(VERSION 3.5)
project(arm11_40)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    arm11_1516_testsuite/lib/json_pure-1.5.3/ext/json/ext/generator/generator.c
    arm11_1516_testsuite/lib/json_pure-1.5.3/ext/json/ext/generator/generator.h
    arm11_1516_testsuite/lib/json_pure-1.5.3/ext/json/ext/parser/parser.c
    arm11_1516_testsuite/lib/json_pure-1.5.3/ext/json/ext/parser/parser.h
    src/ARMgen.h
    src/assemble.c
    src/bitOper.c
    src/bitOper.h
    src/emulate.c
    src/Makefile)

add_executable(arm11_40 ${SOURCE_FILES})
