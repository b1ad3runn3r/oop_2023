#include "HypertextPackage.hpp"
#include <stdexcept>
#include <format>
#include <sstream>

HypertextPackage::HypertextPackage(const send_recv_ip& ips, const Message &message, payload_info info, links_arr l_arr) :
FilePackage(ips, message, info) {
    if (l_arr.links != nullptr) {
        links_size = l_arr.links_size;
        links = new Link[links_size];
        std::copy(l_arr.links, l_arr.links + l_arr.links_size, links);
    }
    else {
        links = nullptr;
        links_size = 0;
    }
    type = "HYPERTEXT";
}

std::string HypertextPackage::get_info() const {
    std::ostringstream oss;

    oss << type << ';';
    oss << get_sender() << ';';
    oss << get_receiver() << ';';
    std::string message;

    if (code_type == ASCII) {
        oss << "ASCII;";
        message = msg.get_msg_ascii();
    }
    else {
        oss << "BIN;";
        message = msg.get_msg_hex();
    }

    oss << std::string((info_type == CMD) ? "CMD" : "DATA") + ';';

    if (links != nullptr) {
        for (size_t i = 0; i < links_size; ++i) {
            if (links[i].get_protocol() == FTP) {
                oss << "[FTP," + links[i].get_hostname() + "] ";
            }
            else {
                oss <<  "[HTTP," + links[i].get_hostname() + "] ";
            }
        }
    }

    oss << ';';
    oss << message;

    return oss.str();
}
