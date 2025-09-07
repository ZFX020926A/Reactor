#include "Acceptor.hpp"

Acceptor::Acceptor(string ip, unsigned short port)
: _socket()
, _inetaddress(ip, port)
{
}

Acceptor::~Acceptor()
{
}

// 对外提供的调用接口
void Acceptor::setready()
{
    setreuseraddr(true);
    setreuserport(true);
    setbind();
    setlisten();
}

// 建立连接
int Acceptor::setaccept()
{
    int accfd = accept(_socket.getsockfd(), NULL, NULL);
    if(accfd < 0)
    {
        perror("accept");
    }
    return accfd;
}

// 设置地址复用
void Acceptor::setreuseraddr(bool boo)
{
    int opt = boo;
    int ret = setsockopt(_socket.getsockfd(), SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    if(ret < 0)
    {
        perror("setsockopt");
    }
}

void Acceptor::setreuserport(bool boo)
{
    int opt = boo;
    int ret = setsockopt(_socket.getsockfd(), SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt));
    if(ret < 0)
    {
        perror("setsockopt");
    }
}

// bind绑定ip和port到文件描述符
void Acceptor::setbind()
{
    int ret = bind(_socket.getsockfd(), (const struct sockaddr *)_inetaddress.getaddrin(), sizeof(_inetaddress));
    if(ret < 0)
    {
        perror("bind");
    }
}

// 设置监听合集
void Acceptor::setlisten(int listennums)
{
    int ret = listen(_socket.getsockfd(), listennums);
    if(ret < 0)
    {
        perror("listen");
    }
}
