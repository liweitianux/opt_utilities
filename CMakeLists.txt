cmake_minimum_required(VERSION 2.6)
PROJECT(opt_utilities,CXX)
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR})

set(CMAKE_VERBOSE_MAKEFILE true)

find_package(ltdl REQUIRED)

add_subdirectory(example)
add_subdirectory(interface)
add_subdirectory(dynamical_fit)

include_directories (${PROJECT_SOURCE_DIR} ${LTDL_INCLUDE_DIRS})

#message(${LTDL_LIBRARIES})
set(LIBRARY_OUTPUT_PATH,lib)
ADD_LIBRARY(opt STATIC interface/opt.cc)
ADD_EXECUTABLE(test_fitter example/test_fitter.cpp)
ADD_EXECUTABLE(test_optimizer example/test_optimizer.cpp)
ADD_EXECUTABLE(dynamical_fit.out dynamical_fit/dynamical_fit.cpp)

target_link_libraries(dynamical_fit.out ${LTDL_LIBRARIES})

