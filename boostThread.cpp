#include <boost/thread.hpp>
#include <iostream>

void wait(int seconds)
{

    boost::this_thread::sleep(boost::posix_time::seconds(seconds));
}
void thread_()
{

    try
    {
        for (int i = 0; i < 5; ++i)
        {
            wait(1);
            std::cout << i << std::endl;
        }
    }
    catch (boost::thread_interrupted &)
    {
        std::cout << "there is an error in the code" << std::endl;
    }
}

int main()
{
    boost::thread t(thread_);
    std::cout << " get thread id: " << t.get_id() << std::endl;
    std::cout << "harware concurreency CPU :" << boost::thread::hardware_concurrency() << std::endl;
    wait(2);
    t.interrupt();
    t.join();

    return 0;
}
