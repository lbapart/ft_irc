#include "Server.hpp"
#include "Channel.hpp"
#include "Client.hpp"

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " <port> <password> !" << std::endl;
        return 1;
    }
    try
    {
        std::stringstream port(argv[1]);
        ushort _port;
        port >> _port;
        if (port.fail())
            throw std::invalid_argument("Invalid port");
        Server server(_port, std::string(argv[2]));
        server.run();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}
