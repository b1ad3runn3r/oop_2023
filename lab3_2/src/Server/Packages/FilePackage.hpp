#ifndef FILE_PACKAGE_HPP
#define FILE_PACKAGE_HPP

#include "Package.hpp"
//#include "HypertextPackage.h"

class HypertextPackage;

class FilePackage : public Package {
protected:
    code_t code_type;
    info_t info_type;

public:
    /**
     * Constructor from IP addresses, message and payload info
     * @param ips sender and receiver IP addresses
     * @param message message
     * @param info payload type
     */
    FilePackage(const send_recv_ip& ips, const Message& message, payload_info info);

    /**
     * Get package info (overrided)
     * @return string with detailed info
     */
    [[nodiscard]] std::string get_info() const override;

    /**
     * Code type getter
     * @return code type
     */
    [[nodiscard]] code_t get_code_type() const noexcept { return code_type; }

    /**
     * Info type getter
     * @return info type
     */
    [[nodiscard]] info_t get_info_type() const noexcept { return info_type; }

    /**
     * Convert to HypertextPackage
     * @return HypertextPackage created instance
     */
    [[nodiscard]] HypertextPackage convert_to_hypertext() const ;
};

#endif // FILE_PACKAGE_HPP
