#include "TaskQueue.hpp"


TaskQueue::TaskQueue(size_t sz)
:_que()
,_size(sz)
,_mutex()
,_notfull(_mutex)   // 这个地方传入_mutex的原因是， 
,_notempty(_mutex)  // _这两个初始化会调用Condition的构造函数进行初始化，而他们的构造函数是一个需要MutexLock的函数
{
}

bool TaskQueue::empty() const
{
    return _que.size() == 0;
}

bool TaskQueue::full() const
{
    return _que.size() == _size;
}

void TaskQueue::push(Element ele)
{
    _mutex.lock(); // 先上锁
    while(full()) // 在判断室友有空间
    {
        _notfull.wait(); // 如果没有空间则在满信号量上面等待
    }
    
    _que.push(ele); // 将元素信息加入到队列中
    _notempty.notify_one(); // 通知在空信号量上等待的消费者
    _mutex.unlock(); // 解锁
}

Element TaskQueue::pop()
{
    _mutex.lock();
    while(empty())
    {
        _notempty.wait();
    }

    Element ret = _que.front(); 
    _que.pop();
    _notfull.notify_one();
    _mutex.unlock();

    return ret;
}


