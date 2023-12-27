#include "TransportTable.hpp"
#include "../Server/Server.hpp"
#include <sstream>

const std::string& TransportTable::get_server_hostname(const Server &server) noexcept {
    return server.get_hostname();
}

const std::string& TransportTable::get_server_ip(const Server &server) noexcept {
    return server.get_ip();
}

TransportTable& TransportTable::operator=(const TransportTable &other) {
    if (this != &other) {
        table = other.table;
    }

    return *this;
}

TransportTable& TransportTable::operator=(TransportTable &&other) noexcept {
    if (this != &other) {
        table = std::move(other.table);
    }

    return *this;
}

void TransportTable::add_package(const std::shared_ptr<Package>& package) {
    if (package == nullptr) {
        throw std::invalid_argument("Invalid package provided!");
    }

    table_key_t key = {package->get_receiver(), package->get_package_type()};
    table.insert(std::pair<table_key_t, std::shared_ptr<Package>>(key, package));
}

void TransportTable::drop_package(const std::string& addr, const std::string& type) {
    if (addr.empty() || type.empty()) {
        throw std::invalid_argument("Invalid ip address!");
    }

    table_key_t key = {addr, type};
    table.erase(key);
}

std::shared_ptr<Package> TransportTable::find_package(const std::string& addr, const std::string& type) {
    if (addr.empty() || type.empty()) {
        throw std::invalid_argument("Invalid ip address or type!");
    }

    table_key_t key = {addr, type};
    auto iter = table.find(key);

    if (iter != table.end()) {
        return iter->second;
    }
    else {
        return nullptr;
    }
}

std::ostringstream &operator<< (std::ostringstream& oss, const TransportTable& tbl) noexcept {
    try {
        for (const auto  &iter : tbl.table) {
            oss << iter.first.first << ';';
            oss << iter.first.second << ';';
            oss << iter.second->get_info() << '\n';
        }
    }
    catch (...) {
        oss.setstate(std::ios_base::failbit);
    }

    return oss;
}
