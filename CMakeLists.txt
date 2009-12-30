cmake_minimum_required(VERSION 2.6)
PROJECT(opt_utilities,CXX)

add_subdirectory(example)
add_subdirectory(interface)

include_directories (${PROJECT_SOURCE_DIR})

set(LIBRARY_OUTPUT_PATH,lib)
ADD_LIBRARY(opt STATIC interface/opt.cc)
ADD_EXECUTABLE(test_fitter example/test_fitter.cpp)
ADD_EXECUTABLE(test_optimizer example/test_optimizer.cpp)
