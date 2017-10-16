#include <list>
#include <mutex>
#include <algorithm>

std::list<int> some_list;      //全局变量
std::mutex some_mutex;          //全局的互斥量保护

//这两个函数中对数据的访问是互斥的
//list_contains()不可能看到正在被add_to_list()修改的列表
void add_to_list(int new_value)
{
    std::lock_guard<std::mutex> guard(some_mutex);
    
    some_list.push_back(new_value);
}
bool list_contains(int value_to_find)
{
    std::lock_guard<std::mutex> guard(some_mutex);
    return std::find(some_list.begin(),some_list.end(),value_to_find)
        != some_list.end();
}

#include <iostream>

int main()
{
    add_to_list(42);
    std::cout<<"contains(1)="<<list_contains(1)<<", contains(42)="<<list_contains(42)<<std::endl;
}
