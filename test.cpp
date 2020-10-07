#include "threadpool.h"
#include <iostream>
#include <fstream>
#include <string>

/* c++ 多线程文档写入*/
void foundFile()
{
    std::ofstream file_;
    for (int i = 0; i < 10; ++i)
    {
        auto f_str = std::to_string(i);
        file_.open("/home/jon/桌面/fileTest/" + f_str + ".txt", std::ios::trunc);
        file_.close();
    }
}

void ofile()
{

    for (int i = 0; i < 10; ++i)
    {
        auto f_str = std::to_string(i);
        std::ofstream file_("/home/jon/桌面/fileTest/" + f_str + ".txt");
        for (int j = 0; j < 1000000; ++j)
        {
            file_ << "===========" << j << "===========\n";
        }
        file_.close();
    }
}

int main()
{
    foundFile();
    //std::threadpool pool(4);
    //pool.commit(ofile);
    //ofile();
    return 0;
}
