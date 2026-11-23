cmake_minimum_required(VERSION 3.20)

project(copilot_cpp_workshop LANGUAGES CXX VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(BUILD_TESTING "Build the CTest suite" ON)
option(ENABLE_SANITIZERS "Enable AddressSanitizer and UBSan" OFF)
option(USE_ONNX_RUNTIME "Use a real ONNX Runtime backend" OFF)

if(MSVC)
  add_compile_options(/W4 /permissive-)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

if(ENABLE_SANITIZERS AND NOT MSVC)
  add_compile_options(-fsanitize=address,undefined -fno-omit-frame-pointer)
  add_link_options(-fsanitize=address,undefined)
endif()

if(USE_ONNX_RUNTIME)
  message(FATAL_ERROR
    "The real ONNX Runtime backend is not wired in by default. "
    "Point onnxruntime_DIR at an approved local package, add the find_package call here, "
    "and link it to edge_inference. The lab default is the reference backend.")
endif()

add_library(edge_inference
  src/input_reader.cpp
  src/preprocessing.cpp
  src/tensor.cpp
  src/model.cpp
  src/postprocessing.cpp
  src/benchmark.cpp
)

target_include_directories(edge_inference PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_compile_features(edge_inference PUBLIC cxx_std_17)

add_executable(edge_inference_cli cli/main.cpp)
target_link_libraries(edge_inference_cli PRIVATE edge_inference)

add_executable(edge_benchmark benchmark/benchmark.cpp)
target_link_libraries(edge_benchmark PRIVATE edge_inference)

if(BUILD_TESTING)
  enable_testing()

  find_package(Boost 1.70 REQUIRED)

  add_executable(edge_unit_tests
    tests/main.cpp
    tests/test_preprocessing.cpp
    tests/test_postprocessing.cpp
    tests/test_model.cpp
  )
  target_link_libraries(edge_unit_tests PRIVATE edge_inference Boost::headers)

  add_test(NAME preprocessing_tests
    COMMAND edge_unit_tests --run_test=PreprocessingTest/*)
  add_test(NAME postprocessing_tests
    COMMAND edge_unit_tests --run_test=PostprocessingTest/*)
  add_test(NAME model_tests
    COMMAND edge_unit_tests --run_test=ModelTest/*)
endif()
