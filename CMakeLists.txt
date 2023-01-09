cmake_minimum_required(VERSION 3.5)

project(Hello)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lib)

aux_source_directory(src SRC_FILES)
add_executable(main ${SRC_FILES})
target_include_directories(main PRIVATE lib/include)
target_link_libraries(main protolib)

aux_source_directory(test TEST_FILES)
add_executable(test ${TEST_FILES})
target_include_directories(test PRIVATE lib/include)
target_link_libraries(test protolib)
