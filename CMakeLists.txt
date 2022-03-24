cmake_minimum_required(VERSION 3.18)
project(libnetwork)

set(NAME network)
set(CONAN_CMAKE_OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake")
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

if(EXISTS ${CONAN_CMAKE_OUTPUT})
    include(${CONAN_CMAKE_OUTPUT})
    conan_basic_setup(TARGETS)
else()
    message(FATAL_ERROR "conanbuildinfo.cmake not found. Run conan install")
endif()

if (UNIX)
    add_compile_options(-Wall -Wextra)
endif()

if (DEFINED ENABLE_TESTING AND "${ENABLE_TESTING}" STREQUAL "yes")
    message(STATUS "ENABLE_TESTING=yes detected, enabling testing")
    add_subdirectory(tests)
endif()

add_subdirectory(include/)
add_subdirectory(src/)

add_library(
    ${NAME} SHARED
        ${INCLUDES}
        ${SRCS}
)

target_precompile_headers(${NAME} PUBLIC ${INCLUDES})

target_include_directories(
    ${NAME}
        PUBLIC
        include/
)

conan_target_link_libraries(
        ${NAME}
        CONAN_PKG::asio
)