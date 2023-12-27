#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>

#include "../Defines/Defines.hpp"
#include "../TransportTable/TransportTable.hpp"

class Server {
private:
    std::string hostname;
    TransportTable table;
    std::string ip;

public:
    /**
     * Constructor from hostname and IP
     * @param host hostname of the server
     * @param ip_addr ip address of the server
     * @throws std::invalid_argument if host or ip_addr is empty
     */
    Server(const std::string &host, const std::string& ip_addr);

    /**
     * Constructor from hostname, IP and transport table
     * @param host hostname of the server
     * @param ip_addr ip address of the server
     * @throws std::invalid_argument if host or ip_addr is empty
     */
    Server(const std::string &host, const std::string& ip_addr, TransportTable &t_table);

    /**
     * Copy constructor
     * @param other instance of to copy
     */
    Server(const Server &other);

    /**
     * Move constructor
     * @param other std::move() of instance to copy
     */
    Server(Server &&other) noexcept;

    /**
     * Copy assignment operator
     * @param other instance to copy
     * @return reference to itself
     */
    Server& operator= (const Server &other);

    /**
     * Move assignment operator
     * @param other instance to move
     * @return reference to itself
     */
    Server& operator= (Server &&other) noexcept;

    /**
     * Hostname getter
     * @return const reference to hostname
     */
    [[nodiscard]] const std::string& get_hostname() const noexcept { return hostname; }

    /**
     * IP address getter
     * @return const reference to IP address
     */
    [[nodiscard]] const std::string& get_ip() const noexcept { return ip; }

    /**
     * Transport table getter
     * @return const reference to transport table
     */
    [[nodiscard]] const TransportTable& get_table() const noexcept { return table; }

    /**
     * Transport table getter
     * @return reference to transport table
     */
    [[nodiscard]] TransportTable& get_table() noexcept { return table; }
};

#endif // SERVER_HPP
