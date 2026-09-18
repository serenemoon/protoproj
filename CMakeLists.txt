# Catch2 is vendored under Catch2/ and needs CMake >= 3.16
cmake_minimum_required(VERSION 3.16)

project(Hello)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

# MinGW links the C++ runtime dynamically by default; those DLLs are not always
# first in PATH, which makes the tests uncompilable-to-run (catch_discover_tests
# runs them at build time). Link the runtime statically instead.
if(MINGW)
    add_link_options(-static)
endif()

add_subdirectory(lib)

aux_source_directory(src SRC_FILES)
add_executable(main ${SRC_FILES})
target_include_directories(main PRIVATE lib/include)
target_link_libraries(main protolib)

include(CTest)

if(BUILD_TESTING)
    # vendored Catch2 v3, see Catch2/LICENSE.txt
    add_subdirectory(Catch2)

    aux_source_directory(test TEST_FILES)
    # the target name "test" is reserved by CTest, keep the binary name as before
    add_executable(tests ${TEST_FILES})
    set_target_properties(tests PROPERTIES OUTPUT_NAME test)
    target_include_directories(tests PRIVATE lib/include)
    target_link_libraries(tests protolib Catch2::Catch2WithMain)

    # register each TEST_CASE as a ctest test
    list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/Catch2/extras)
    include(Catch)
    catch_discover_tests(tests)
endif()
