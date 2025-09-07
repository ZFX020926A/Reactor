#include "Socket.hpp"

#include <iostream>
#include <tcpHeader.h>

using std::cout;
using std::endl;

Socket::Socket()
: _sockfd(-1)
{
    _sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(_sockfd < 0)
    {
        perror("socket");
    }
}

Socket::~Socket()
{
    if(_sockfd > 0)
    {
        close(_sockfd);
    }
}

void Socket::ShuntDownWrite()
{
    // 主动断开连接是 关闭写端
    shutdown(_sockfd, SHUT_WR);
}

