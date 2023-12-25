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
    Server(const std::string &host, const std::string& ip_addr);
    Server(const std::string &host, const std::string& ip_addr, TransportTable &t_table);

    Server(const Server &other);
    Server(Server &&other) noexcept;

    Server& operator= (const Server &other);
    Server& operator= (Server &&other) noexcept;

    [[nodiscard]] const std::string& get_hostname() const noexcept { return hostname; }
    [[nodiscard]] const std::string& get_ip() const noexcept { return ip; }
    [[nodiscard]] const TransportTable& get_table() const noexcept { return table; }
    [[nodiscard]] TransportTable& get_table() noexcept { return table; }
};

#endif // SERVER_HPP
