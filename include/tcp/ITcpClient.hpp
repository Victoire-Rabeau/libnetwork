#ifndef ITCPCLIENT_HPP
#define ITCPCLIENT_HPP

#include <functional>

#include "Address.hpp"

namespace network::tcp
{
    /**
     * @interface ITcpClient
     * @brief Implements a tcp client interface
     * @tparam Request The request type
     * @tparam Response The response type
     */
    template <typename Request, typename Response>
    class ITcpClient
    {
        public:
            virtual ~ITcpClient() = default;

            /**
             * @brief Connects the client to a peer
             * @param[in] peer The peer's address
             */
            void connect(Address const &peer) = 0;

            /**
             * @brief Disconnects the client from it's peer
             */
            void disconnect() = 0;

            /**
             * @brief Sends data to the connected peer synchronously
             * @param[in] packet The data to send
             * @return The number of bytes sent
             */
            [[nodiscard]] virtual std::size_t send(Response const &packet) = 0;

            /**
             * @brief Receives the data from the connected peer synchronously
             * @return The read data
             */
            [[nodiscard]] virtual Request receive() = 0;

            /**
             * @brief Sends data to the connected peer asynchronously
             * @param[in] packet The data to send
             * @param[in, out] callback The function called when the data is sent
             */
            virtual void asyncSend(Response const &packet, std::function<void (int)> &&callback) noexcept = 0;

            /**
             * @brief Receives data from the connected peer asynchronously
             * @param[in, out] callback The function called when the data is received
             */
            virtual void asyncReceive(std::function<void (int, Request &)> &&callback) noexcept = 0;
    };
}

#endif //ITCPCLIENT_HPP
