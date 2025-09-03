#include "SocketIO.hpp"

#include <tcpHeader.h>

SocketIO::SocketIO(int fd)
: _fd(fd)
{
}

SocketIO::~SocketIO()
{
}

int SocketIO::readn(char *buff, int len)
{
    int flage = len;
    char *pbuff = buff;

    while(flage > 0)
    {
        int ret = recv(_fd, pbuff, flage, 0);
        if(ret == -1 && errno == EINTR)
        {
            continue;
        }
        else if (ret == -1)
        {
            perror("recv");
            return len - flage;
        }
        else if (ret == 0)
        {
            // 断开连接
            return len - flage;
        }
        else
        {
            flage -= ret;   
            pbuff += ret;
        }
    }
    return len - flage;
}

int SocketIO::writen(const char *buff, int len)
{
    int flage = len;
    const char *pbuff = buff;
    while(flage > 0)
    {
        int ret = send(_fd, pbuff, flage, 0);
        if(ret == -1 && errno == EINTR)
        {
            continue;
        }
        else if(ret == -1)
        {
            perror("send");
            return len - flage;
        }
        else
        {
            flage -= ret;
            pbuff += ret;
        }

    }
    return len - flage;
}

int SocketIO::readline(char *buff, int len)
{
    int flage = len - 1;
    char *pbuff = buff;
    int total = 0;
    while (flage > 0)
    {
        int ret = recvpeek(pbuff, flage);

        // 找换行符
        for(int i = 0; i < ret; ++i)
        {
            
            if(pbuff[i] == '\n')
            {
                // 找到换行符
                int size = i + 1;
                ret = recv(_fd, pbuff, size, 0);
                total += ret;
                pbuff[i] = '\0';
                return total;
            }
        }

        // 没有找到换行符
        ret = readn(pbuff, ret);
        flage -= ret;
        pbuff += ret;
        total += ret;
    }

    // 这里表示 buff已经存储满了， 但是没有找到换行符
    buff[len - 1] = '\0';
    return len - 1;
}

int SocketIO::recvpeek(char *buff, int len)
{
    int ret = -1;
    do
    {
        ret = recv(_fd, buff, len, MSG_PEEK);
    } while (ret == -1 && errno == EINTR);

    return ret;
}