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
    FilePackage(const send_recv_ip& ips, const Message& message, payload_info info);

    [[nodiscard]] std::string get_info() const override;

    [[nodiscard]] code_t get_code_type() const noexcept { return code_type; }
    [[nodiscard]] info_t get_info_type() const noexcept { return info_type; }

    [[nodiscard]] HypertextPackage convert_to_hypertext() const ;
};

#endif // FILE_PACKAGE_HPP
