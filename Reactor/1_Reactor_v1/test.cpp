#include "Acceptor.hpp"
#include "TcpConnection.hpp"
#include <iostream>

using std::cout;
using std::endl;

int main()
{
    Acceptor acceptor("0.0.0.0", 8000);
    acceptor.setready();
    printf(">> server start listening.\n");

    int netfd = acceptor.setaccept();
    TcpConnection conn(netfd);
    //cout << conn.toString() << " has connected successfully." << endl;

    conn.sendmsg("welcome to server.");
    cout << "receive msg: " << conn.recvmsg() << endl;


    return 0;
}