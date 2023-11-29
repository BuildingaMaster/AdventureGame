cmake_minimum_required(VERSION 3.0.0)
project(AdventureGame VERSION 0.1.0 LANGUAGES C CXX)

#include(CTest)

option(ENABLE_TESTS "Enables building the unit tests" ON)

if(ENABLE_TESTS)
  find_package(GTest REQUIRED)
  if (GTEST_FOUND)
    enable_testing()
    message(STATUS "Using the system gtest")
    include(GoogleTest)
    #include_directories(${GTEST_INCLUDE_DIRS})
    add_subdirectory(AdventureTimeTesting)
  endif()
  # Force gtest to link the C runtime dynamically on Windows in order to avoid runtime mismatches.
  #set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
else()
  message(STATUS "Unit tests are disabled")
endif()

#add_executable(AdventureGame main.cpp)
add_subdirectory(AdventureGame)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
