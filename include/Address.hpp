#ifndef ADDRESS_HPP
#define ADDRESS_HPP

#include <cstdint>
#include <string>

namespace network
{
    /**
     * @struct Address
     * @brief Represents an address
     */
    struct Address
    {
        /**
         * @brief Creates a new Address object from a std::string
         * @param[in] ip The ip address
         * @param[in] port The port
         */
        Address(std::string const &ip, std::uint16_t port);

        std::uint32_t ip;
        std::uint16_t port;
    };
}

#endif //ADDRESS_HPP
