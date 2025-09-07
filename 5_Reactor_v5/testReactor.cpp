#include "EchoServer.hpp"

void test(){
   
    EchoServer server(4, 10, "0.0.0.0", 8000);

    server.Strart();
}

int main()
{
 test();
 return 0;
}
