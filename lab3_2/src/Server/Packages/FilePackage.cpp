#include "FilePackage.hpp"
#include "HypertextPackage.hpp"
#include <stdexcept>

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

    return sender + receiver + code + info + message;
}

HypertextPackage FilePackage::convert_to_hypertext() const {
    send_recv_ip ips = {sndr_ip, recv_ip};
    payload_info info = {code_type, info_type};
    links_arr l_arr = {nullptr, 0};

    return {ips, msg, info, l_arr};
}
