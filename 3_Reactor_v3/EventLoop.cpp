#include "EventLoop.hpp"

#include <iostream>

using std::cout;
using std::endl;


EventLoop::EventLoop(Acceptor &acc)
: _epollfd(createpollfd())
, _accfd(acc)
, _islooping(false)
, _veceventarr(1024)
{
    //cout << "EventLoop 构造函数 " << endl;
    addepollevent(_accfd.getacceptfd());
}

EventLoop::~EventLoop()
{
}

void EventLoop::loop()
{
    _islooping = true;
    while(_islooping)
    {
        epollwaitevent();
    }
}

void EventLoop::unloop()
{
    _islooping = false;
}

int EventLoop::createpollfd()
{
    int ret = epoll_create1(0);
    if(ret < 0)
    {
        perror("epoll_create1");
    }
    return ret;
}

void EventLoop::addepollevent(int fd)
{
    struct epoll_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.data.fd = fd;
    ev.events = EPOLLIN;
    // ---------------------------
    cout << "fd = " << fd << endl;

    int ret = epoll_ctl(_epollfd, EPOLL_CTL_ADD, fd, &ev);
    if(ret < 0)
    {
        cout << "EventLoop epoll_ctl error" << endl;
        perror("epoll_ctl");
    }
}

void EventLoop::delepollevent(int fd)
{
    struct epoll_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.data.fd = fd;
    int ret = epoll_ctl(_epollfd, EPOLL_CTL_DEL, fd, NULL);
    if(ret < 0)
    {
        perror("epoll_ctl");
    }
}

void EventLoop::epollwaitevent()
{
    int nready = epoll_wait(_epollfd, _veceventarr.data(), _veceventarr.size(), 5000);
    if(nready == -1 && errno == EINTR)
    {
        return ;
    }
    else if(nready == -1)
    {
        perror("epoll_wait");
    }
    else if(nready == 0)
    {
        cout << "epoll_wait time_out" << endl;
    }
    else
    {
        for(int i = 0; i < nready; ++i)
        {
            int fd = _veceventarr[i].data.fd;
            if(fd == _accfd.getacceptfd())
            {
                // 这是一个新连接
                handlenewconnection();
            }
            else
            {
                // 这是一个旧连接 发来的消息
                handlemessage(fd);
            }
        }
    }

}

void EventLoop::handlenewconnection()
{
    // 新连接需要创建TcpConnection对象
    int newfd = _accfd.setaccept(); // 这个fd是三次握手建立成功得fd

    // 将新连接添加到epoll上面监听
    addepollevent(newfd);

    // 创建一个TcpConnection对象 使用shared_ptr管理
    TcpConnectionfd conn(new TcpConnection(newfd));

    // 为新连接注册回调函数 用于处理事件
    conn->setcallback(_onconnection, _onmessage, _onclose);

    // 处理新连接
    conn->handlenewconnectionCallback();

    // 将新连接添加到map中进行管理
    _conns[newfd] = conn;

}

void EventLoop::handlemessage(int fd)
{
    auto itear = _conns.find(fd);
    if(itear != _conns.end())
    {
        bool isclose = itear->second->isclose(); // 判断连接是否关闭
        if(isclose)
        {
            // 连接已经关闭
            itear->second->handlecloseCallback();

            // 从epoll中删除该连接
            delepollevent(fd);

            // 从map中删除该连接
            _conns.erase(itear);
        }
        else
        {
            // 连接没有关闭
            itear->second->handlemessageCallback();
        }
    }
}

void EventLoop::setcallback(TcpConnectionCallback cb1,
                            TcpConnectionCallback cb2,
                            TcpConnectionCallback cb3)
    {
        _onconnection = cb1;
        _onmessage = cb2;
        _onclose = cb3;
    }