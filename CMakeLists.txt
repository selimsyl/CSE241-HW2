cmake_minimum_required(VERSION 3.14)

project(HW2)

set(GTEST_ROOT "/home/maninblack/Documents/googletest/googletest" CACHE PATH "Path to googletest")

include(CTest)
#enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

file(GLOB_RECURSE sources peg.cpp)
file(GLOB_RECURSE testsource tdd.cxx)

add_library(peg SHARED ${sources})

add_executable(pegApp peg)
add_executable(pegTest ${testsource})

target_compile_features(pegApp PUBLIC cxx_std_11)
target_compile_features(pegTest PUBLIC cxx_std_17)

add_dependencies(pegApp peg)
add_dependencies(pegTest pegApp)

target_link_libraries(pegTest ${GTEST_BOTH_LIBRARIES} pthread peg)
gtest_add_tests(TARGET pegTest)

add_custom_command( TARGET pegTest 
                    POST_BUILD
                    COMMAND ctest
                    VERBATIM
                  )

#gtest_discover_tests(peg)
