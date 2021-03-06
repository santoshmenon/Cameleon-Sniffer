#include "DnsDump.hh"

DnsDump::DnsDump(const NetworkInterface &iface, std::ostream *out, const std::string &filename)
    : ASniffer(iface, "DnsDump", "udp and dst port 53", out), _filename(filename)
{
}

DnsDump::~DnsDump(void)
{
    // Reinterpret cast ?
    static_cast<std::ofstream*>(_out)->close();
}

bool DnsDump::handler(PDU &pdu)
{
    // EthernetII / IP / UDP / RawPDU
    EthernetII eth = pdu.rfind_pdu<EthernetII>();
    IP ip = eth.rfind_pdu<IP>();
    UDP udp = ip.rfind_pdu<UDP>();
    DNS dns = udp.rfind_pdu<RawPDU>().to<DNS>();

    // Is it a DNS query?
    if(dns.type() == DNS::QUERY)
    {
        // Let's see if there's any query for an "A" record.
        for(const DNS::Query &query : dns.queries())
        {
            if(query.type() == DNS::A)
                *_out << getDate() << "\t" << ip.src_addr() << "  -->  " << query.dname() << std::endl;
        }
    }
    return true;
}

std::string DnsDump::info(void) const { return "Filename = " + _filename; }

std::string DnsDump::help(void) { return std::string("Start DNS queries dumper.\n") + "\tOptions : <file>"; }

const std::string DnsDump::getDate(void) const
{
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];

    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);

    return buf;
}
