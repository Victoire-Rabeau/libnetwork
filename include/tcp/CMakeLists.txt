set(
        TCP_INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/ITcpClient.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ITcpListener.hpp
        ${ASIO_TCP_INCLUDES}
        PARENT_SCOPE
)