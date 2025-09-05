#include "Acceptor.hpp"
#include "TcpConnection.hpp"
#include "EventLoop.hpp"

#include <iostream>
using std::cout;
using std::endl;

// 回调函数
void onconnetion(TcpConnectionfd conn)
{
    cout << "有新连接上来了" << conn << endl;
}

void onmessage(TcpConnectionfd conn)
{
    string msg = conn->recvmsg();
    cout << "有新消息到来了 : " << msg << endl;

    conn->sendmsg(msg);
}

void onclose(TcpConnectionfd conn)
{
    cout << "连接断开了" << conn << endl;
}





void test(){
    // v1 test
    // Acceptor acc("0.0.0.0", 8000);
    // acc.setready();
    // int accfd = acc.setaccept();
    // cout << "ready ok" << endl;

    // TcpConnection tcpcon(accfd);
    // cout << "have connection" << endl;

    // tcpcon.sendmsg("i am server, who are you ?");
    // //char buff[1024] = {0};
    // // while(1)
    // // {
    //     //memset(buff, 0, sizeof(buff));
    // cout << "rserver recv msg:" << tcpcon.recvmsg() << endl;
    // //}
    

    // v2 test
    Acceptor acc("0.0.0.0", 8000);
    acc.setready();
    cout << "ready ok" << endl;

    EventLoop loop(acc);
    loop.setcallback(onconnetion, onmessage, onclose);

    loop.loop();    
   
}

int main()
{
 test();
 return 0;
}
