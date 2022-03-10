#ifndef ASIOTCPCLIENT_HPP
#define ASIOTCPCLIENT_HPP

#include "tcp/ITcpClient.hpp"

namespace network::tcp
{
    template <typename Request, typename Response>
    class AsioTcpClient : public ITcpClient<Request, Response>
    {
        public:

            AsioTcpClient(std::uint16_t port)
            {}

            ~AsioTcpClient() override = default;

            void connect(Address const &peer) override
            {}

            void disconnect() override
            {}

            [[nodiscard]] std::size_t send(Response const &packet) override
            {}

            [[nodiscard]] Request receive() override
            {}

            void asyncSend(Response const &packet, std::function<void (int)> &&callback) noexcept override
            {}

            virtual void asyncReceive(std::function<void (int, Request &)> &&callback) noexcept override
            {}
    };
}

#endif //ASIOTCPCLIENT_HPP
