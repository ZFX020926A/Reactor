#ifndef __MYTASK_H__
#define __MYTASK_H__

#include "TcpConnection.hpp"

#include <string>
using std::string;

class Mytask
{
private:
    string _msg;
    TcpConnectionfd _conn;
public:
    Mytask(const string msg, TcpConnectionfd conn)
    : _msg(msg)
    , _conn(conn)
    {

    }

    ~Mytask()
    {

    }

    void process()
    {
        string response = _msg;
        _conn->sendinLoop(response);
    }
};

#endif // !__MYTASK_H__