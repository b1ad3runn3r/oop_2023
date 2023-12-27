#include "MailPackage.hpp"
#include "FilePackage.hpp"
#include <stdexcept>
#include <algorithm>
#include <format>
#include <sstream>

MailPackage::MailPackage(const send_recv_ip& ips, std::string& user, const Message& message) {
    if (ips.sender.empty() || ips.receiver.empty()) {
        throw std::invalid_argument("Nullptr provided as argument!");
    }

    if (user.empty() || user.length() > 20) {
        throw std::invalid_argument("Invalid username provided!");
    }

    sndr_ip = ips.sender;
    recv_ip = ips.receiver;
    username = user;
    msg = message;
    type = "MAIL";
}

std::string MailPackage::get_info() const {
    std::ostringstream oss;
    oss << type << ';';
    oss << get_sender() << ';';
    oss << get_receiver() << ';';
    oss << get_username() << ';';
    oss << msg.get_msg_hex();

    return oss.str();
}

FilePackage MailPackage::convert_to_file() const {
    send_recv_ip ips = {sndr_ip, recv_ip};
    payload_info info = {ASCII, DATA};

    return {ips, msg, info};
}

bool operator==(const MailPackage &p, const MailPackage &other) noexcept {
    if (p.username != other.username) {
        return false;
    }

    if (!(p.msg == other.msg)) {
        return false;
    }

    for (size_t i = 0; i < 4; ++i) {
        if (p.sndr_ip[i] != other.sndr_ip[i] || p.recv_ip[i] != other.sndr_ip[i]) {
            return false;
        }
    }



    return true;
}
