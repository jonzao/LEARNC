#include <boost/asio.hpp>
#include <memory>
#include <iostream>
#include <string>
#include <functional>
#include <ctime>
#include<win

using boost::asio::ip::tcp;

std::string make_daytime_string()
{

    using namespace std;
    auto now = time(nullptr);
    return ctime(&now);
}

class tcp_connection : public std::enable_shared_from_this<tcp_connection>
{
public:
    using pointer = std::shared_ptr<tcp_connection>;
    static pointer create(boost::asio::io_service &io_service)
    {
        return pointer(new tcp_connection(io_service));
    }
    tcp::socket &socket() { return socket_; }
    void start()
    {
        auto self = shared_from_this();
        message_ = make_daytime_string();
        boost::asio::async_write(socket, boost::asio::buffer(message_),
                                 [self = std::move(self)](auto error, auto bytes_transferred) {
                                     self->handle_write(error, bytes_transferred);
                                 });
        // boost::asio::async_write(socket, boost::asio::buffer(message_),
        //                          boost::bind(&tcp_connection::handle_write,
        //                                      shared_from_this(),
        //                                      boost::asio::placeholders::error,
        //                                      boost::asio::placeholders::bytes_transferred));
    }

private:
    tcp_connection(boost::asio::io_service &io_service) : socket_(io_service) {}
    void handle_write(const boost::system::error_code &, size_t) {}
    tcp::socket socket_;
    std::string message_;
};
class tcp_server
{
public:
    tcp_server(boost::asio::io_service &io_service) : acceptor_(io_service, tcp::endpoint(tcp::v4(), 8080))
    {
        start_accept();
    }

private:
    void start_accept()
    {
        auto new_connection = tcp_connection::create(acceptor_.get_io_service());
        acceptor_.async_accept(new_connection->socket(), [this, new_connection](auto error) { this->handle_accept(new_connection, error); });
    }
    void handle_accept(tcp_connection::pointer new_connection, const boost::system::error_code &error)
    {
        if (!error)
        {
            new_connection->start();
        }
        start_accept();
    }
    tcp::acceptor acceptor_;
};
