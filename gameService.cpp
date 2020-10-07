#include <iostream>
#include <boost/asio.hpp>
//#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/asio/steady_timer.hpp>
void callback(const boost::system::error_code &)
{
    std::cout << "非阻塞" << std::endl;
}
int main()
{

    boost::asio::io_service io;
    // boost::asio::deadline_timer t(io, boost::posix_time::seconds(5));
    boost::asio::steady_timer st(io);
    st.expires_from_now(std::chrono::seconds(1));
    st.async_wait(callback);
    io.run();

    std::cout << "helloword boost lib" << std::endl;
    return 0;
}