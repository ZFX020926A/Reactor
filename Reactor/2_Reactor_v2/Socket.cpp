#include "Socket.hpp"

#include <tcpHeader.h>

Socket::Socket()
: _sockfd(-1)
{
    _sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(_sockfd < 0)
    {
        perror("socket");
    }
}

// 利用栈对象的生命周期来管理资源 RAII思想：资源获取即初始化
Socket::Socket(int fd)
: _sockfd(fd)
{
}

Socket::~Socket()
{
    if(_sockfd > 0)
    {
        close(_sockfd);
    }
}

int Socket::getsockfd()
{
    return _sockfd;
}

void Socket::ShuntDownWrite()
{
    // 在主动关闭时关闭写端
    shutdown(_sockfd, SHUT_WR);
}
