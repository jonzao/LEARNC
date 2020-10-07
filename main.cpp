#include <iostream>
#include <list>
#include <thread>
#include <atomic>
#include <mutex>
#include <chrono>
#include <cstring>
#include <vector>
#include <condition_variable>
class Message
{
public:
    const std::string &data() const
    {
        return m_data;
    }
    Message(std::string d) : m_data(std::move(d))
    {
    }

private:
    std ::string m_data;
};
std::condition_variable cv;
std::mutex t_mutex;
std::atomic<bool> ready{false};
std::atomic<bool> quit{false};
std::list<Message> globalList;
std::atomic<int> totlal_size{0};
void worker(int i)

{
    while (!ready)
    {
    }
    while (!quit)
    {
        // std::lock_guard<std::mutex> lock(t_mutex);
        std::unique_lock<std::mutex> lock(t_mutex);
        cv.wait(lock, [] { return quit || !globalList.empty(); });
        if (globalList.empty())
        {
            continue;
        }
        auto iter = globalList.begin();

        totlal_size += std::strlen((*iter).data().c_str());
        globalList.erase(iter);
        //  std::cout << "tid: " << i << std::endl;
    }
}
int main()
{
    const auto threadcount = 4;
    for (int i = 0; i < 10000; ++i)
    {
        globalList.push_back("this is a test" + std::to_string(i));
    }
    std::vector<std::thread> pool;
    for (int i = 0; i < threadcount; ++i)
    {
        pool.emplace_back(worker, i);
    }
    ready = true;

    for (int i = 0; i < 10000; ++i)
    {
        std::lock_guard<std::mutex> lock(t_mutex);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        globalList.push_back(std::string("second"));
        cv.notify_one();
    }

    while (true)
    {
        std::lock_guard<std::mutex> lock(t_mutex);
        if (globalList.empty())
        {
            quit = true;
            cv.notify_all();
            break;
        }
    }

    for (auto &v : pool)
    {
        if (v.joinable())
        {
            v.join();
        }
    }
    return 0;
}
