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
            // 使用线程分离，主线程结束，子线程可能还在运行
			// 这时就会访问已经销毁的变量
        }
    }
};


void oops()
{
    int some_local_state=0;
    func my_func(some_local_state);
    std::thread my_thread(my_func);
    my_thread.detach();		
    //线程和std::thread对象分离，	
    //之后，std::thread 对象就与实际执行的线程无关了，并且这个线程也无法加入
}

int main()
{
    oops();
	getchar();
}
