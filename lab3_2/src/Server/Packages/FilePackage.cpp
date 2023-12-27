#include "FilePackage.hpp"
#include "HypertextPackage.hpp"
#include <stdexcept>
#include <sstream>

FilePackage::FilePackage(const send_recv_ip& ips, const Message& message, payload_info info) {
    if (ips.sender.empty() || ips.receiver.empty()) {
        throw std::invalid_argument("Nullptr provided as argument!");
    }

    sndr_ip = ips.sender;
    recv_ip = ips.receiver;
    msg = message;
    code_type = info.code_type;
    info_type = info.info_type;
    type = "FILE";
}

std::string FilePackage::get_info() const {
    std::ostringstream oss;

    oss << type << ';';
    oss << get_sender() << ';';
    oss << get_receiver() << ';';
    std::string message;

    if (code_type == ASCII) {
        oss <<  "ASCII;";
        message = msg.get_msg_ascii();
    }
    else {
        oss << "BIN;";
        message = msg.get_msg_hex();
    }

    oss << std::string((info_type == CMD) ? "CMD" : "DATA") + ';';
    oss << message;

    return oss.str();
}

HypertextPackage FilePackage::convert_to_hypertext() const {
    send_recv_ip ips = {sndr_ip, recv_ip};
    payload_info info = {code_type, info_type};
    links_arr l_arr = {nullptr, 0};

    return {ips, msg, info, l_arr};
}
