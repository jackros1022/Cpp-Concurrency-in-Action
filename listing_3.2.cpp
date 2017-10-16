#include <mutex>

class some_data
{
    int a;
    std::string b;
public:
    void do_something()
    {}
};

class data_wrapper
{
private:
    some_data data;
    std::mutex m;
public:
    template<typename Function>
    void process_data(Function func)
    {
        std::lock_guard<std::mutex> l(m);
        func(data);         //传递了保护数据的引用
    }
};

some_data* unprotected;

void malicious_function(some_data& protected_data)
{
    unprotected=&protected_data;
}

data_wrapper x;

void foo()
{
    x.process_data(malicious_function);         //传递一个恶意函数
    unprotected->do_something();                //在无保护的情况下访问保护数据
}

int main()
{
    foo();
}
