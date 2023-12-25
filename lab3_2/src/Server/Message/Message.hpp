#ifndef MESSAGE_H
#define MESSAGE_H

#include <cstddef>
#include <string>
#include "../Defines/Defines.hpp"

class Message {
private:
    size_t msg_len;
    unsigned char *msg;

public:
    explicit Message(size_t len = 0, const byte *message = nullptr);

    Message(const Message& old);

    Message(Message &&old) noexcept :
    msg_len(old.msg_len), msg(old.msg) {
        old.msg = nullptr;
        old.msg_len = 0;
    }

    Message& operator= (const Message& old);
    Message& operator= (Message&& old) noexcept;
    friend bool operator==(const Message& m, const Message& other) noexcept;

    ~Message() { delete[] msg; }

    [[nodiscard]] size_t get_msg_len() const noexcept { return msg_len; }
    [[nodiscard]] const unsigned char *get_msg() const noexcept { return msg; }

    [[nodiscard]] std::string get_msg_hex() const;
    [[nodiscard]] std::string get_msg_ascii() const { return {reinterpret_cast<char *>(msg)}; }
};
#endif // MESSAGE_H
