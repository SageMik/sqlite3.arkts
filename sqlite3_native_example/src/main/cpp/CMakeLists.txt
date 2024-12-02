# the minimum version of CMake.
cmake_minimum_required(VERSION 3.5.0)
project(sqlite3_ohos)

set(NATIVERENDER_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

if(DEFINED PACKAGE_FIND_FILE)
    include(${PACKAGE_FIND_FILE})
endif()

include_directories(${NATIVERENDER_ROOT_PATH}
                    ${NATIVERENDER_ROOT_PATH}/include)

set(sqlite3_native_LIBRARY_DIR "${NATIVERENDER_ROOT_PATH}/../../../../sqlite3_native_library/build/default/intermediates/libs/default/${OHOS_ARCH}/")
add_library(sqlite3_native_library SHARED IMPORTED)
set_target_properties(sqlite3_native_library
    PROPERTIES
    IMPORTED_LOCATION ${sqlite3_native_LIBRARY_DIR}/libsqlite3.so)

add_library(sqlite3_native_example SHARED napi_init.cpp)
target_link_libraries(sqlite3_native_example PUBLIC
    libace_napi.z.so
    libhilog_ndk.z.so
    sqlite3_native_library
)