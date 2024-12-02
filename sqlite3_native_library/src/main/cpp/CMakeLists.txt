# SQLite 3.46.0
# https://github.com/simolus3/sqlite-native-libraries/blob/ed5fcb2d54e67672103ec3b4d3508df591f39dfa/sqlite3-native-library/cpp/CMakeLists.txt

cmake_minimum_required(VERSION 3.14)
project(
    sqlite3_native_library
    VERSION 3
    LANGUAGES C
)

include(FetchContent)

FetchContent_Declare(
  sqlite3
  URL https://sqlite.org/2024/sqlite-autoconf-3460000.tar.gz
)
FetchContent_MakeAvailable(sqlite3)

set(CMAKE_C_FLAGS "-O3")

add_library(sqlite3 SHARED "${sqlite3_SOURCE_DIR}/sqlite3.c")
target_include_directories(sqlite3 PRIVATE ${sqlite3_SOURCE_DIR})

target_compile_definitions(sqlite3 PUBLIC
    SQLITE_ENABLE_DBSTAT_VTAB
    SQLITE_ENABLE_FTS5
    SQLITE_ENABLE_RTREE
    SQLITE_DQS=0
    SQLITE_DEFAULT_MEMSTATUS=0
    SQLITE_TEMP_STORE=2
    SQLITE_MAX_EXPR_DEPTH=0
    SQLITE_STRICT_SUBTYPE=1
    SQLITE_OMIT_AUTHORIZATION
    SQLITE_OMIT_DECLTYPE
    SQLITE_OMIT_DEPRECATED
    SQLITE_OMIT_PROGRESS_CALLBACK
    SQLITE_OMIT_SHARED_CACHE
    SQLITE_OMIT_TCL_VARIABLE
    SQLITE_OMIT_TRACE
    SQLITE_USE_ALLOCA
    SQLITE_UNTESTABLE
    SQLITE_HAVE_ISNAN
    SQLITE_HAVE_LOCALTIME_R
    SQLITE_HAVE_LOCALTIME_S
    SQLITE_HAVE_MALLOC_USABLE_SIZE
    SQLITE_HAVE_STRCHRNUL
)

#cmake_minimum_required(VERSION 3.5.0)
#project(sqlite3_native_library_ohos C)
#include(FetchContent)
#FetchContent_Declare(
#  sqlite3_native_library
#  GIT_REPOSITORY https://github.com/simolus3/sqlite-native-libraries
#  GIT_TAG ed5fcb2d54e67672103ec3b4d3508df591f39dfa
#)
#FetchContent_MakeAvailable(sqlite3_native_library)
#add_subdirectory(${sqlite3_native_library_SOURCE_DIR}/sqlite3-native-library/cpp ${sqlite3_native_library_BINARY_DIR})
