cmake_minimum_required (VERSION 4.4)

project (CMakeTemplate)
enable_language (CXX)

include (CTest)
include (GoogleTest)

# MSVC links ASan builds against clang_rt.asan_dynamic-x86_64.dll, which lives next to cl.exe
# and is not on PATH. Copy it beside the executable in the Asan configuration so the program
# (and gtest's post-build test discovery) can start. Call this before gtest_discover_tests().
function (copy_asan_runtime target)
  if (NOT MSVC)
    return ()
  endif ()
  get_filename_component (MSVC_BIN_DIR "${CMAKE_CXX_COMPILER}" DIRECTORY)
  set (ASAN_RUNTIME "${MSVC_BIN_DIR}/clang_rt.asan_dynamic-x86_64.dll")
  add_custom_command (TARGET ${target} POST_BUILD
    COMMAND "$<$<CONFIG:Asan>:${CMAKE_COMMAND};-E;copy_if_different;${ASAN_RUNTIME};$<TARGET_FILE_DIR:${target}>>"
    COMMAND_EXPAND_LISTS
  )
endfunction ()

add_subdirectory (external)

add_subdirectory (examplelib)

add_executable (main src/main.cpp)
target_compile_features (main PUBLIC cxx_std_23)
target_include_directories (main PUBLIC include)
target_link_libraries (main PUBLIC examplelib)
copy_asan_runtime (main)

