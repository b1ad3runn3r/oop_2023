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
    /**
     * Default constructor
     */
    explicit Link() : hostname(), protocol(HTTP) {};

    /**
     * Constructor from hostname and protocol
     * @param host hostname
     * @param proto protocol
     */
    Link(std::string& host, proto_t proto) :
    hostname(host), protocol(proto) {};

    /**
     * Constructor from hostname and protocol
     * @param host hostname
     * @param proto protocol
     */
    Link(const char *host, proto_t proto) :
    hostname(host), protocol(proto) {};

    /**
     * Protocol getter
     * @return protocol
     */
    [[nodiscard]] proto_t get_protocol() const noexcept { return protocol; }

    /**
     * Hostname getter
     * @return hostname
     */
    [[nodiscard]] const std::string& get_hostname() const noexcept { return hostname; }

    /**
     * Hostname setter from char[]
     * @param host hostname
     * @return reference to itself
     */
    Link& set_hostname(const std::string& host) { hostname = host; return *this; }

    /**
     * Hostname setter from std::string
     * @param host hostname
     * @return reference to itself
     */
    Link& set_hostname(const char *host) { hostname = host; return *this; }

    /**
     * Protocol setter
     * @param proto protocol
     * @return reference to itself
     */
    Link& set_protocol(proto_t proto) noexcept { protocol = proto; return *this; }

    /**
     * Comparison operator
     * @param l link
     * @param other another link
     * @return comparison result
     */
    friend bool operator==(const Link &l, const Link &other) {
        return l.hostname == other.hostname &&
                l.protocol == other.protocol;
    }
};

#endif // LINK_HPP
