#include "pizone/pizone.hpp"
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread.hpp>
#include <future>
#include <iostream>
#include <memory>

void set_promise(std::promise<int> &p) { p.set_value(100); }

int main() {
    boost::asio::io_context io_context;

    boost::promise<int> boost_p;
    boost::future<int> boost_i;

    std::shared_ptr<boost::asio::deadline_timer> timer =
        std::make_shared<boost::asio::deadline_timer>(io_context, boost::posix_time::seconds(2));
    timer->async_wait([](const boost::system::error_code &ec) { std::cout << "2 seconds passed" << std::endl; });

    std::cout << "Hello, world!!" << std::endl;
    io_context.run();
    std::cout << "Bye, world!" << std::endl;
    return 0;
}
