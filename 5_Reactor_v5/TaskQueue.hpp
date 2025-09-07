#ifndef __TASKQUEUE_H__
#define __TASKQUEUE_H__

#include "Condition.hpp"
#include "MutexLock.hpp"
#include "Task.hpp"
#include <queue>

using std::queue;

using Element = Task;

class TaskQueue
{
public:
    TaskQueue(size_t sz);
    bool full() const;
    bool empty() const;
    void push(Element &&);
    Element pop();
private:
    queue<Element> _que; // 用来存储生产的数据
    size_t     _size; // 用来表示存储器的容量
    MutexLock  _mutex;
    Condition  _notfull;
    Condition  _notempty;
    bool       _isstop;
};


#endif // !TASKQUEUE_H

