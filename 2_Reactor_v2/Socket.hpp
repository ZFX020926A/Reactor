#ifndef __SOCKET_H__
#define __SOCKET_H__

// 此类包含了所有对于文件描述符 的处理函数
class Socket
{
private:
    int _sockfd;
public:
    Socket();
    Socket(int fd);
    ~Socket();
    int getsockfd();
    void ShuntDownWrite();
};




#endif // !__SOCKET_H__