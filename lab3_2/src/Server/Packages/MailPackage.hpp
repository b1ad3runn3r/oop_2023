#ifndef MAIL_PACKAGE_HPP
#define MAIL_PACKAGE_HPP

#include "Package.hpp"

class FilePackage;

class MailPackage : public Package {
private:
    std::string username;

public:
    MailPackage(const send_recv_ip& ips, std::string& user, const Message& message);

    [[nodiscard]] std::string get_info() const override;

    std::string& get_username() { return username; }
    [[nodiscard]] const std::string& get_username() const { return username; }

    [[nodiscard]] FilePackage convert_to_file() const ;

    friend bool operator==(const MailPackage &p, const MailPackage &other) noexcept;
};

#endif //MAIL_PACKAGE_HPP
