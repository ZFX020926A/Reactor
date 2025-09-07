#ifndef __TCPCONNECTION_H__
#define __TCPCONNECTION_H__

#include "Socket.hpp"
#include "SocketIO.hpp"
#include "InetAddress.hpp"


#include <memory>
#include <functional>
#include <string>
using std::shared_ptr;
using std::string;
using std::function;

class EventLoop;

class TcpConnection;
using TcpConnectionfd = shared_ptr<TcpConnection>;
using TcpConnectionCallback = function<void(TcpConnectionfd)>;

class TcpConnection
: public std::enable_shared_from_this<TcpConnection>
{
private:
    Socket _sockfd;
    SocketIO _socketio;
    InetAddress _localaddr;
    InetAddress _peeraddr;
    TcpConnectionCallback _onconnection;
    TcpConnectionCallback _onmessage;
    TcpConnectionCallback _onclose;

    // v4
    EventLoop *_loop;
public:
    //  TcpConnection(int fd);
    // v4
    TcpConnection(int fd, EventLoop *loop);
    ~TcpConnection();
    void sendmsg(const string &msg);
    string recvmsg();
    bool isclose();
    void setcallback(TcpConnectionCallback cb1,
                     TcpConnectionCallback cb2,
                     TcpConnectionCallback cb3);
    void handlenewconnectionCallback();
    void handlemessageCallback();
    void handlecloseCallback();

    // v4
    void sendinLoop(const string &msg);

private:
    InetAddress getlocaladdr();
    InetAddress getpeeraddr();
};




#endif // !__TCPCONNECTION_H__