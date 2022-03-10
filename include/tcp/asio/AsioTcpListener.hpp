#ifndef ASIOTCPLISTENER_HPP
#define ASIOTCPLISTENER_HPP

#include "tcp/ITcpListener.hpp"

namespace network::tcp
{
    template <typename Request, typename Response>
    class AsioTcpListener : public ITcpListener<Request, Response>
    {
        public:

            AsioTcpListener(std::uint16_t port)
            {}

            ~AsioTcpListener() override = default;

            void run(std::function<void (int, std::unique_ptr<network::tcp::ITcpClient<Request, Response>>)> &&callback) noexcept override
            {}

            void stop() noexcept override
            {}
    };
}

#endif //ASIOTCPLISTENER_HPP
