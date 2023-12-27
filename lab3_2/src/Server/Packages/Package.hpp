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
    /**
     * Get package info
     * @return string with detailed info
     */
    [[nodiscard]] virtual std::string get_info() const = 0;

    /**
     * Package type getter
     * @return package type
     */
    [[nodiscard]] const std::string& get_package_type() const noexcept { return type; }

    /**
     * Sender getter
     * @return sender's IP address
     */
    [[nodiscard]] const std::string& get_sender() const noexcept { return sndr_ip; }

    /**
     * Receiver getter
     * @return receiver's IP address
     */
    [[nodiscard]] const std::string& get_receiver() const noexcept { return recv_ip; }
};

#endif //PACKAGE_HPP
