#include "Server.hpp"
#include <stdexcept>

Server::Server(const std::string &host, const std::string& ip_addr) {
    if (host.empty() || ip_addr.empty()) {
        throw std::invalid_argument("Invalid ip or hostname!");
    }

    hostname = host;
    ip = ip_addr;
}

Server::Server(const std::string &host, const std::string& ip_addr, TransportTable &t_table) {
    if (host.empty() || ip_addr.empty()) {
        throw std::invalid_argument("Invalid ip or hostname!");
    }

    hostname = host;
    table = t_table;
    ip = ip_addr;
}

Server::Server(const Server &other) {
    ip = other.ip;
    hostname = other.hostname;
    table = other.table;
}

Server::Server(Server &&other) noexcept {
    std::swap(ip, other.ip);
    std::swap(hostname, other.hostname);
    std::swap(table, other.table);
}

Server& Server::operator= (const Server &other) {
    if (this != &other) {
        ip = other.ip;
        hostname = other.hostname;
        table = other.table;
    }

    return *this;
}

Server& Server::operator= (Server &&other) noexcept {
    if (this != &other) {
        std::swap(ip, other.ip);
        std::swap(hostname, other.hostname);
        std::swap(table, other.table);
    }

    return *this;
}
