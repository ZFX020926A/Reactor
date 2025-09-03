#include "Acceptor.hpp"
#include "TcpConnection.hpp"

#include <iostream>
using std::cout;
using std::endl;

void test(){
    Acceptor acc("0.0.0.0", 8000);
    acc.setready();
    int accfd = acc.setaccept();
    cout << "ready ok" << endl;

    TcpConnection tcpcon(accfd);
    cout << "have connection" << endl;

    tcpcon.sendmsg("i am server, who are you ?");
    //char buff[1024] = {0};
    // while(1)
    // {
        //memset(buff, 0, sizeof(buff));
    cout << "rserver recv msg:" << tcpcon.recvmsg() << endl;
    //}
    
}

int main()
{
 test();
 return 0;
}
