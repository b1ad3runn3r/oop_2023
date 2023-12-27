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

    /**
     * Server hostname getter
     * @param server server
     * @return server's hostname
     */
    [[nodiscard]] static const std::string& get_server_hostname(const Server &server) noexcept;

    /**
     * Server IP address getter
     * @param server server
     * @return server's IP
     */
    [[nodiscard]] static const std::string& get_server_ip(const Server &server) noexcept;

public:
    /**
     * Default constructor
     */
    explicit TransportTable() : table() {};

    /**
     * Copy constructor
     * @param other instance to be copied
     */
    TransportTable(const TransportTable &other) { table = other.table; }

    /**
     * Move constructor
     * @param old instance to be moved
     */
    TransportTable(TransportTable &&old) noexcept { std::swap(table, old.table); }

    /**
     * Copy assignment
     * @param other instance to be copied
     * @return reference to itself
     */
    TransportTable& operator=(const TransportTable &other);

    /**
     * Move assignment
     * @param other instance to be moved
     * @return reference to itself
     */
    TransportTable& operator=(TransportTable &&other) noexcept;

    /**
     * Comparison operator
     * @param t
     * @param other
     * @return
     */
    [[nodiscard]] friend bool operator==(const TransportTable &t, const TransportTable &other) noexcept {
        return t.table == other.table;
    }

    /**
     * Check table for emptiness
     * @return whether table is empty or not
     */
    [[nodiscard]] bool empty() const noexcept { return table.empty(); }

    /**
     * Table getter
     * @return reference to table
     */
    [[nodiscard]] const auto& get_table() const noexcept { return table; }

    /**
     * Add package to table
     * @param package pointer to Package
     */
    void add_package(const std::shared_ptr<Package>& package);

    /**
     * Drop package
     * @param addr IP address
     * @param type type of package
     */
    void drop_package(const std::string& addr, const std::string& type);

    /**
     * Find package
     * @param addr IP address
     * @param type type of package
     * @return pointer to Package if found and nullptr if not
     */
    std::shared_ptr<Package> find_package(const std::string& addr, const std::string& type);

    /**
     * Print operator
     * @param oss output stringstream
     * @param tbl table
     * @return modified stringstream
     */
    friend std::ostringstream &operator<< (std::ostringstream& oss, const TransportTable& tbl) noexcept;
};

#endif // TRANSPORT_TABLE_HPP
