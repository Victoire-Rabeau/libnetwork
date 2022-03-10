#include "Address.hpp"

namespace network
{
    Address::Address(std::string const &_ip, std::uint16_t _port)
    {
        ip = std::stol(_ip);
        port = _port;
    }
}