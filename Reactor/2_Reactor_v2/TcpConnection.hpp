#ifndef __TCPCONNECTION_H__
#define __TCPCONNECTION_H__

#include "Socket.hpp"
#include "SocketIO.hpp"
#include "InetAddress.hpp"

class TcpConnection
{
private:
    Socket _sockfd;
    SocketIO _socketio;
    InetAddress _localaddr;
    InetAddress _peeraddr;
public:
    TcpConnection(int fd);
    ~TcpConnection();
    void sendmsg(const string &msg);
    string recvmsg();
    bool isclose();
private:
    InetAddress getlocaladdr();
    InetAddress getpeeraddr();
};




#endif // !__TCPCONNECTION_H__