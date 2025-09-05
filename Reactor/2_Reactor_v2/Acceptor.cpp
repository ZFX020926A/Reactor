#include "Acceptor.hpp"


Acceptor::Acceptor(string ip, unsigned short port)
: _socket()
, _inetaddress(ip, port)
{
}

Acceptor::~Acceptor()
{
}

void Acceptor::setready()
{
    setreuseraddr(true);
    setreuserport(true);
    setbind();
    setlisten();
}

int Acceptor::setaccept()
{
    int accfd = accept(_socket.getsockfd(), NULL, NULL);
    if(accfd < 0)
    {
        perror("accept");
    }

    return accfd;
}

void Acceptor::setreuseraddr(bool boo)
{
    // 地址复用
    int opt = boo;
    int ret = setsockopt(getacceptfd(), SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    if(ret < 0)
    {
        perror("setsockopt");
    }
}

void Acceptor::setreuserport(bool boo)
{
    // 端口复用
    int opt = boo;
    //int ret = setsockopt(_socket.getsockfd(), SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt));
    int ret = setsockopt(getacceptfd(), SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt));
    if(ret < 0)
    if(ret < 0)
    {
        perror("setsockopt");
    }

}

void Acceptor::setbind()
{
    //int ret = bind(_socket.getsockfd(), (const struct sockaddr *)_inetaddress.getaddrin(), sizeof(_inetaddress));
    int ret = bind(getacceptfd(), (const struct sockaddr *)_inetaddress.getaddrin(), sizeof(_inetaddress));
    if(ret < 0)
    {
        perror("bind");
    }
}

void Acceptor::setlisten()
{
    //int ret = listen(_socket.getsockfd(), 20000);
    int ret = listen(getacceptfd(), 20000);
    if(ret < 0)
    {
        perror("listen");
    }
}

int Acceptor::getacceptfd()
{
    return _socket.getsockfd();
}
