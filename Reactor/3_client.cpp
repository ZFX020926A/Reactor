#include <iostream>
#include <tcpHeader.h>
#include <cstdlib>
#include <unistd.h>

using std::cout;
using std::endl;


int test(){
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    //ERROR_CHECK(sockfd, 0, "socket");

    struct sockaddr_in sockaddrin;
    memset(&sockaddrin, 0, sizeof(sockaddrin));

    sockaddrin.sin_family = AF_INET;
    sockaddrin.sin_addr.s_addr = inet_addr("8.148.74.118");
    sockaddrin.sin_port = htons(8000);

    int connectfd = connect(sockfd, (const struct sockaddr*)&sockaddrin, sizeof(sockaddrin));
    //ERROR_CHECK(connectfd, 0, "connect");

    // 使用select进行监听
    fd_set fdset;
    
    char buff[1024] = {0};
    while(1)
    {
        FD_ZERO(&fdset);
        FD_SET(STDIN_FILENO, &fdset);
        FD_SET(sockfd, &fdset);

        int ret = select(sockfd + 1, &fdset, NULL, NULL, NULL);
        //ERROR_CHECK(ret, 0, "select");

        if(FD_ISSET(STDIN_FILENO, &fdset))
        {
            // 有输入事件发生
            memset(buff, 0, sizeof(buff));
            read(STDIN_FILENO, buff, sizeof(buff));

            int sendfd = send(sockfd, buff, strlen(buff), 0);
            //ERROR_CHECK(sendfd, 0, "send");
            cout << "发送：" << buff << endl;
        }

        // if(FD_ISSET(STDIN_FILENO, &fdset))
        // {
        //     memset(buff, 0, sizeof(buff));
        //     int n = read(STDIN_FILENO, buff, sizeof(buff)-1);
        //     if(n > 0) {
        //         buff[n] = '\0';
        //         // 去除换行符
        //         char* p = strchr(buff, '\n');
        //         if(p) *p = '\0';
        //         send(sockfd, buff, strlen(buff), 0);
        //         cout << "发送：" << buff << endl;
        //     }
        // }

        // if(FD_ISSET(STDIN_FILENO, &fdset)) {
        //     memset(buff, 0, sizeof(buff));
        //     ret = read(STDIN_FILENO, buff, sizeof(buff));
        //     //printf("\nread %d bytes from stdin.\n", ret);

        //     //发送给服务器
        //     send(sockfd, buff, strlen(buff), 0);
        //     //printf("\nsend %d bytes.\n", ret);
        // }

        if(FD_ISSET(sockfd, &fdset))
        {
            memset(buff, 0, sizeof(buff));
            int ret = recv(sockfd, buff, sizeof(buff), 0);
            if(ret == 0)
            {
                cout << "服务器关闭" << endl;
                break;
            }
            if(ret > 0)
            {
                buff[ret] = '\0';
                cout << "接收到：" << buff << endl; 
            }
            
        }
    }
    close(sockfd);
    return 0;
}


int main()
{
 test();
 return 0;
}
