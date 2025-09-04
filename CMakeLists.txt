cmake_minimum_required (VERSION 3.27)

project (CMakeTemplate)

add_subdirectory (external)
include (cmake/PackageAddTests.cmake)

option (BUILD_TEST "Build the tests" ON)
if (BUILD_TEST)
    enable_testing()
    include (GoogleTest)
endif ()

if(MSVC)
  # Force to always compile with W4
  add_compile_options (/W4 /EHsc "$<$<CONFIG:Debug>:/Od>" "$<$<CONFIG:Debug>:/fsanitize=address>" "$<$<CONFIG:Release>:/O2>")
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  # Update if necessary
  add_compile_options (-Wall -pedantic)
endif()

add_subdirectory (examplelib)

add_executable (main src/main.cpp)
target_compile_features (main PUBLIC cxx_std_23)
target_include_directories (main PUBLIC include)
target_link_libraries (main PUBLIC examplelib)

