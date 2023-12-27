#include "Message.hpp"
#include <sstream>

Message::Message(size_t len, const byte *message) {
    if (message == nullptr) {
        msg = new byte[1];
        msg[0] = 0;
        msg_len = 0;
    }
    else {
        msg_len = len;
        msg = new byte[msg_len + 1];
        std::copy(message, message + len + 1, msg);
    }
}

Message::Message(const Message& old) {
    auto new_msg = new byte[old.msg_len + 1];
    std::copy(old.msg, old.msg + old.msg_len + 1, new_msg);

    msg_len = old.msg_len;
    //delete[] msg;
    msg = new_msg;
}

Message& Message::operator= (const Message& old) {
    if (this != &old) {
        auto new_msg = new byte[old.msg_len + 1];
        std::copy(old.msg, old.msg + old.msg_len + 1, new_msg);

        msg_len = old.msg_len;
        delete[] msg;
        msg = new_msg;
    }

    return *this;
}

Message& Message::operator= (Message&& old) noexcept {
    if (this != &old) {
        delete[] msg;

        msg = old.msg;
        msg_len = old.msg_len;

        old.msg = nullptr;
        old.msg_len = 0;
    }
    return *this;
}

bool operator==(const Message& m, const Message& other) noexcept {
    if (m.msg_len != other.msg_len) {
        return false;
    }

    for (size_t i = 0; i < m.msg_len; ++i) {
        if (m.msg[i] != other.msg[i]) {
            return false;
        }
    }

    return true;
}

std::string Message::get_msg_hex() const {
    if (msg[0] == 0) {
        return {"00"};
    }

    std::stringstream ss;
    ss << std::hex;
    for (size_t i = 0; i < msg_len + 1; ++i) {
        ss << static_cast<int>(msg[i]);
    }
    ss << '0';

    return ss.str();
}
