#ifndef ASIOTCPCLIENT_HPP
#define ASIOTCPCLIENT_HPP

#include <asio/ip/tcp.hpp>
#include <asio/read.hpp>
#include <asio/write.hpp>

#include "tcp/ITcpClient.hpp"

namespace network::tcp
{
    template <typename Request, typename Response>
    class AsioTcpClient : public ITcpClient<Request, Response>
    {
        public:

            AsioTcpClient() :
                _ioContext{},
                _tcpSocket{_ioContext},
                _run{false}
            {}

            ~AsioTcpClient() override
            {
                _ioContext.stop();
            }

            void connect(Address const &peer) override
            {
                asio::ip::tcp::endpoint endpoint{asio::ip::address{peer.ip}, peer.port};

                _tcpSocket.connect(endpoint);
                _run = true;
            }

            void disconnect() override
            {
                _run = false;
            }

            [[nodiscard]] std::size_t send(Response const &packet) override
            {
                std::size_t writeSize;

                try {
                    asio::write(_tcpSocket, asio::buffer(&packet, sizeof(Response)));
                } catch (asio::system_error const &e) {
                    throw std::runtime_error{"ERROR(network/tcp/asio/AsioTcpClient): Unable to send data: " + std::string{e.what()}};
                }
                return writeSize;
            }

            [[nodiscard]] Request receive() override
            {
                Request request;

                try {
                    asio::read(_tcpSocket, asio::buffer(request, sizeof(request)));
                } catch (asio::system_error const &e) {
                    throw (std::runtime_error{"ERROR(network/tcp/asio/AsioTcpClient): Unable to receive data: " + std::string{e.what()}});
                }
                return request;
            }

            void asyncSend(Response const &packet, std::function<void (int)> &&callback) noexcept override
            {
                asio::async_write(_tcpSocket, asio::buffer(&packet, sizeof(Response)),
                                  [callback = std::move(callback)] (int errorCode,std::size_t) {
                        callback(errorCode);
                });
            }

            void asyncReceive(std::function<void (int, Request &)> &&callback) noexcept override
            {
                Request request;

                asio::async_read(_tcpSocket, asio::buffer(&request, sizeof(Request)),
                                 [this, callback = std::move(callback), request] (int errorCode, std::size_t) mutable {
                    callback(errorCode, request);
                    if (!_run)
                        return;
                    asyncReceive(std::move(callback));
                });
            }

        private:
            asio::io_context _ioContext;
            asio::ip::tcp::socket _tcpSocket;
            bool _run;
    };
}

#endif //ASIOTCPCLIENT_HPP
