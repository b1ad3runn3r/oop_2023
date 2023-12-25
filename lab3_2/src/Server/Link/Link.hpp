#ifndef LINK_HPP
#define LINK_HPP

#include <string>
#include <utility>
#include "../Defines/Defines.hpp"

class Link {
private:
    std::string hostname;
    proto_t protocol;

public:
    explicit Link() : hostname(), protocol(HTTP) {};

    Link(std::string& host, proto_t proto) :
    hostname(host), protocol(proto) {};

    Link(const char *host, proto_t proto) :
    hostname(host), protocol(proto) {};

    [[nodiscard]] proto_t get_protocol() const noexcept { return protocol; }
    [[nodiscard]] const std::string& get_hostname() const noexcept { return hostname; }

    Link& set_hostname(const std::string& host) { hostname = host; return *this; }
    Link& set_hostname(const char *host) { hostname = host; return *this; }

    Link& set_protocol(proto_t proto) noexcept { protocol = proto; return *this; }

    friend bool operator==(const Link &l, const Link &other) {
        return l.hostname == other.hostname &&
                l.protocol == other.protocol;
    }
};

#endif // LINK_HPP
