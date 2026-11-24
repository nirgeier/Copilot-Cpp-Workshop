cmake_minimum_required(VERSION 3.20)

project(mini_infer LANGUAGES CXX VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(BUILD_TESTING "Build the CTest suite" ON)
option(ENABLE_SANITIZERS "Enable AddressSanitizer and UBSan" OFF)

if(MSVC)
  add_compile_options(/W4 /permissive-)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

if(ENABLE_SANITIZERS AND NOT MSVC)
  add_compile_options(-fsanitize=address,undefined -fno-omit-frame-pointer)
  add_link_options(-fsanitize=address,undefined)
endif()

add_library(mini_infer
  src/normalize.cpp
  src/argmax.cpp
)
target_include_directories(mini_infer PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_compile_features(mini_infer PUBLIC cxx_std_17)

add_executable(mini_infer_cli cli/main.cpp)
target_link_libraries(mini_infer_cli PRIVATE mini_infer)

if(BUILD_TESTING)
  enable_testing()

  find_package(Boost 1.70 REQUIRED)

  add_executable(mini_infer_unit_tests
    tests/main.cpp
    tests/test_normalize.cpp
    tests/test_argmax.cpp
  )
  target_link_libraries(mini_infer_unit_tests PRIVATE mini_infer Boost::headers)

  add_test(NAME normalize_tests
    COMMAND mini_infer_unit_tests --run_test=NormalizeTest/*)
  add_test(NAME argmax_tests
    COMMAND mini_infer_unit_tests --run_test=ArgmaxTest/*)
endif()
