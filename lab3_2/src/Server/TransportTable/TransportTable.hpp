#ifndef TRANSPORT_TABLE_HPP
#define TRANSPORT_TABLE_HPP

#include <string>
#include <memory>
#include <vector>
#include <map>
#include "../Defines/Defines.hpp"
#include "../Packages/Package.hpp"

class Server;

class TransportTable {
    typedef std::pair<std::string, std::string> table_key_t;

private:
    // IP TYPE
    std::multimap< table_key_t, std::shared_ptr<Package> > table;

    [[nodiscard]] static const std::string& get_server_hostname(const Server &server) noexcept;
    [[nodiscard]] static const std::string& get_server_ip(const Server &server) noexcept;

public:
    explicit TransportTable() : table() {};
    TransportTable(const TransportTable &other) = default;
    TransportTable(TransportTable &&old) noexcept : table(std::move(old.table)) {};

    TransportTable& operator=(const TransportTable &other);
    TransportTable& operator=(TransportTable &&other) noexcept;

    [[nodiscard]] friend bool operator==(const TransportTable &t, const TransportTable &other) noexcept {
        return t.table == other.table;
    }

    [[nodiscard]] bool empty() const noexcept { return table.empty(); }

    [[nodiscard]] const auto& get_table() const noexcept { return table; }
    void add_package(const std::shared_ptr<Package>& package);
    void drop_package(const std::string& addr, const std::string& type);
    std::shared_ptr<Package> find_package(const std::string& addr, const std::string& type);

    friend std::ostringstream &operator<< (std::ostringstream& oss, const TransportTable& tbl) noexcept;
};

#endif // TRANSPORT_TABLE_HPP
