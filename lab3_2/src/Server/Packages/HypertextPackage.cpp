#include "HypertextPackage.hpp"
#include <stdexcept>
#include <format>

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
    std::string sender = "sender: " + get_sender() + '\n';
    std::string receiver = "receiver: " + get_receiver() + '\n';
    std::string code;
    std::string message;

    if (code_type == ASCII) {
        code = "code: ASCII\n";
        message = "message: " + msg.get_msg_ascii();
    }
    else {
        code = "code: BIN\n";
        message = "message: " + msg.get_msg_hex();
    }

    std::string info = "info: " + std::string((info_type == CMD) ? "CMD" : "DATA") + '\n';

    std::string str_links = "links: ";
    if (links != nullptr) {
        for (size_t i = 0; i < links_size; ++i) {
            if (links[i].get_protocol() == FTP) {
                str_links += "[FTP," + links[i].get_hostname() + "] ";
            }
            else {
                str_links += "[HTTP," + links[i].get_hostname() + "] ";
            }
        }
    }

    str_links += '\n';

    return sender + receiver + code + info + str_links + message;
}
