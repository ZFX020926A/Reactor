#include "TcpConnection.hpp"


TcpConnection::TcpConnection(int fd)
: _sockfd(fd)
, _socketio(fd)
, _localaddr(getlocaladdr())
, _peeraddr(getpeeraddr())
{
}

TcpConnection::~TcpConnection()
{
}

// 检查连接是否断开 peek缓冲区是否有内容
bool TcpConnection::isclose()
{
    char buff[5] = {0};
    int ret = _socketio.recvpeek(buff, sizeof(buff));

    return ret == 0;
}

void TcpConnection::sendmsg(const string &msg)
{
    int ret = _socketio.writen(msg.data(), msg.size());
}

string TcpConnection::recvmsg()
{
    char buff[65535] = {0};
    int ret = _socketio.readline(buff, sizeof(buff));

    return string(buff, ret);// 用buff缓冲区的前ret个字符构建字符串
}

// 得到本端的ip和端口
InetAddress TcpConnection::getlocaladdr()
{
    struct sockaddr_in addrin;
    memset(&addrin, 0, sizeof(addrin));
    socklen_t addrlen = sizeof(addrin);
    getsockname(_sockfd.getsockfd(), (struct sockaddr *)&addrin, &addrlen);

    return InetAddress(addrin);
}

// 得到对端的ip和端口
InetAddress TcpConnection::getpeeraddr()
{
    struct sockaddr_in addrin;
    memset(&addrin, 0, sizeof(addrin));
    socklen_t addrlen = sizeof(addrin);
    getpeername(_sockfd.getsockfd(), (struct sockaddr *)&addrin, &addrlen);
    
    return InetAddress(addrin);
}