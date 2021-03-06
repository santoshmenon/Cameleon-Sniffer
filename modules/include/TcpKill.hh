#ifndef TCPKILL_HH
#define TCPKILL_HH

#include "ASniffer.hh"
#include "ASender.hh"

using namespace Tins;

class TcpKill : public ASniffer
{
public:
    typedef enum    e_type
    {
        ServerToVictim = 1,
        AllToServer,
        VictimToAll
    }               TYPE;

private:
    const IPv4Address               _dstIp;
    const IPv4Address               _srcIp;
    const int                       _port;
    const TYPE                      _type;
    PacketSender                    _sender;

public:
    // Kill traffic from dstIp:port to srcIp
    TcpKill(const NetworkInterface &iface, std::ostream *out, std::string &dstIp, std::string &srcIp, std::string &port);
    // Kill all traffic from port to srcIP
    TcpKill(const NetworkInterface &iface, std::ostream *out, std::string &srcIp, std::string &port, bool flag);
    // Kill all traffic from dstIp:port
    TcpKill(const NetworkInterface &iface, std::ostream *out, std::string &dstIp, std::string &port);

    ~TcpKill(void) { }

public:
    static std::string              help(void);


    // ASender
public:
    std::string                     info(void) const;
    const std::string               &name(void) const;

    // ASniffer
public:
    bool                            handler(PDU &pdu);
};

#endif // TCPKILL_HH
