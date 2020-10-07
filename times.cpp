#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
using boost::asio::ip::tcp;

std::string make_daytime_string()
{
    using namespace std;
    auto now = time(nullptr);
    return ctime(&now);
}
int main()
{
    try
    {
        boost::asio::io_service io_service;
        tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 8080));
        for (;;)
        {
            tcp::socket socket(io_service);
            acceptor.accept(socket);
            auto message = make_daytime_string();
            boost::system::error_code ignored_error;
            boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
        }
    }
    catch (std::exception &e)
    {
    }
    return 0;
}