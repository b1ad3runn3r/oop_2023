#ifndef HYPERTEXT_PACKAGE_HPP
#define HYPERTEXT_PACKAGE_HPP

#include "../Link/Link.hpp"
#include "FilePackage.hpp"

struct links_arr{
    Link *links;
    size_t links_size;
};

class HypertextPackage : public FilePackage {
private:
    size_t links_size;
    Link *links;

public:
    HypertextPackage(const send_recv_ip& ips, const Message &message, payload_info info, links_arr l_arr);

    ~HypertextPackage() { delete[] links; }

    [[nodiscard]] std::string get_info() const override;

    [[nodiscard]] Link* get_links() const noexcept { return links; }
    [[nodiscard]] size_t get_links_size() const noexcept { return links_size; }
};

#endif // HYPERTEXT_PACKAGE_HPP
