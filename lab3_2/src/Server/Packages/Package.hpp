#ifndef PACKAGE_HPP
#define PACKAGE_HPP

#include <string>
#include "../Message/Message.hpp"
#include "../Defines/Defines.hpp"

class Package {
protected:
    std::string sndr_ip;
    std::string recv_ip;
    Message msg;
    std::string type;

public:
    [[nodiscard]] virtual std::string get_info() const = 0;
    [[nodiscard]] const std::string& get_package_type() const noexcept { return type; }
    [[nodiscard]] const std::string& get_sender() const noexcept { return sndr_ip; }
    [[nodiscard]] const std::string& get_receiver() const noexcept { return recv_ip; }
};

#endif //PACKAGE_HPP
