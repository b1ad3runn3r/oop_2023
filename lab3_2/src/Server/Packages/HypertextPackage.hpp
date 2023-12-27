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
    /**
     * Constructor from IP addresses, message, payload info and links
     * @param ips sender and receiver IP addresses
     * @param message message
     * @param info payload info
     * @param l_arr links array and its length
     */
    HypertextPackage(const send_recv_ip& ips, const Message &message, payload_info info, links_arr l_arr);

    /**
     * Destructor
     */
    ~HypertextPackage() { delete[] links; }

    /**
     * Get package info (overrided)
     * @return string with detailed info
     */
    [[nodiscard]] std::string get_info() const override;

    /**
     * Links getter
     * @return pointer to links array
     */
    [[nodiscard]] Link* get_links() const noexcept { return links; }

    /**
     * Links size getter
     * @return size of the links array
     */
    [[nodiscard]] size_t get_links_size() const noexcept { return links_size; }
};

#endif // HYPERTEXT_PACKAGE_HPP
