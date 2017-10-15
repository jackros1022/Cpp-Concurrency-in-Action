#include <vector>
#include <thread>
#include <algorithm>
#include <functional>

void do_work(unsigned id)
{}

void f()
{
    std::vector<std::thread> threads;
    for(unsigned i=0;i<20;++i)
    {
        threads.push_back(std::thread(do_work,i));
        //线程所做的工作都是独立的，并且结果仅会受到共享数据的影响
    }
    std::for_each(threads.begin(),threads.end(),std::mem_fn(&std::thread::join));
}

int main()
{
    f();
}
