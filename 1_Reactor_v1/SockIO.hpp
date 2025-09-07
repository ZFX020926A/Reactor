#ifndef __SOCKETIO_H__
#define __SOCKETIO_H__
class SockIO
{
public:
    SockIO(int fd);
    ~SockIO();
    
    int writen(const char *buff, int len);
    int readline(char *buff, int len);
    int readn(char *buff, int len);
    int recvpeek(char *buff, int len);
private:
    int _fd;
};



#endif // !__SOCKETIO_H__