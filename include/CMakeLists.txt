add_subdirectory(tcp/)

set(
        INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/Address.hpp
        ${TCP_INCLUDES}
        PARENT_SCOPE
)