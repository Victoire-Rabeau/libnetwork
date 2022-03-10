#ifndef ITCPLISTENER_HPP
#define ITCPLISTENER_HPP

#include <memory>

#include "ITcpClient.hpp"

namespace network::tcp
{
    /**
     * @interface ITcpListener
     * @brief Implements a tcp listener that accepts connections
     * @tparam Request The request's type
     * @tparam Response The response's type
     */
    template <typename Request, typename Response>
    class ITcpListener
    {
        public:

             virtual ~ITcpListener() = default;

            /**
             * @brief Runs the listener
             */
            virtual void run(std::function<void (int, std::unique_ptr<network::tcp::ITcpClient<Request, Response>>)> &&callback) noexcept = 0;

            /**
             * @brief Stops the listener
             */
            virtual void stop() noexcept = 0;

    };
}

#endif //ITCPLISTENER_HPP
