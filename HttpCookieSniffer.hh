#ifndef HTTPCOOKIESNIFFER_HH
#define HTTPCOOKIESNIFFER_HH

#include "ASniffer.hh"
#include "Http.hh"

class HttpCookieSniffer : public ASniffer
{
private:
    const std::string               _filename;
    const std::vector<std::string>  _keys;

public:
    HttpCookieSniffer(Core &core, std::ostream *out, const std::string &filename, const std::vector<std::string> &keys);
    ~HttpCookieSniffer(void) { }

    // AModule
public:
    virtual std::string             info(void);
    static std::string              help(void);

    // ASniffer
public:
    bool                            handler(PDU &pdu);

};

#endif // HTTPCOOKIESNIFFER_HH