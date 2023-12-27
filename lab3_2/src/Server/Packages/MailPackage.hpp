#ifndef MAIL_PACKAGE_HPP
#define MAIL_PACKAGE_HPP

#include "Package.hpp"

class FilePackage;

class MailPackage : public Package {
private:
    std::string username;

public:
    /**
     * Constructor from IP addresses, username and message
     * @param ips sender and receiver IP addresses
     * @param user username
     * @param message message
     */
    MailPackage(const send_recv_ip& ips, std::string& user, const Message& message);

    /**
     * Get package info (overrided)
     * @return string with detailed info
     */
    [[nodiscard]] std::string get_info() const override;

    /**
     * Username getter
     * @return username reference
     */
    std::string& get_username() { return username; }

    /**
     * Username getter (const)
     * @return const reference to username
     */
    [[nodiscard]] const std::string& get_username() const { return username; }

    /**
     * Convert to FilePackage
     * @return Instance of created FilePackage
     */
    [[nodiscard]] FilePackage convert_to_file() const ;

    /**
     * Comparison operator
     * @param p MailPackage
     * @param other another MailPackage
     * @return comparison result
     */
    friend bool operator==(const MailPackage &p, const MailPackage &other) noexcept;
};

#endif //MAIL_PACKAGE_HPP
