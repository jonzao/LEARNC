#include <iostream>
#include <string>
using namespace std;

class A
{
public:
    A();
    ~A() noexcept(false)
    {
        throw string("error");
    }
};

void test()
{

    try
    {
        A a();
    }
    catch (string e)
    {

        cout << "object  A  is except : " + e << endl;
    }
}
int main()
{
    test();
    cout << "xxx" << endl;
    return 0;
}