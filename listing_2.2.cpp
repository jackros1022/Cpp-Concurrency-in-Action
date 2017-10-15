#include <thread>

void do_something(int& i)
{
    ++i;
}

struct func
{
    int& i;

    func(int& i_):i(i_){}

    void operator()()
    {
        for(unsigned j=0;j<1000000;++j)
        {
            do_something(i);
        }
    }
};

void do_something_in_current_thread()
{}

void f()
{
    int some_local_state=0;
    func my_func(some_local_state);
    std::thread t(my_func);
    try
    {
        do_something_in_current_thread();
    }
    catch(...)
    {
        t.join();	//1.发生异常在join()函数之前，join()就不会被调用
					//2.所以，在catch中再次加入join()函数
					//3.从而避免生命周期的问题
        throw;
    }
    t.join();
}

int main()
{
    f();
}
