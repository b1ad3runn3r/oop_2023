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
    /**
     * Constructor from message and message length
     * @param len message length
     * @param message message
     */
    explicit Message(size_t len = 0, const byte *message = nullptr);

    /**
     * Copy constructor
     * @param other instance to be copied
     */
    Message(const Message& other);

    /**
     * Move constructor
     * @param old instance to be moved
     */
    Message(Message &&old) noexcept :
    msg_len(old.msg_len), msg(old.msg) {
        old.msg = nullptr;
        old.msg_len = 0;
    }

    /**
     * Copy assignment
     * @param old instance to be copied
     * @return reference to itself
     */
    Message& operator= (const Message& old);

    /**
     * Move assignment
     * @param old instance to be moved
     * @return reference to itself
     */
    Message& operator= (Message&& old) noexcept;

    /**
     * Comparison operator
     * @param m message
     * @param other another message
     * @return result of the comparison
     */
    friend bool operator==(const Message& m, const Message& other) noexcept;

    /**
     * Destructor
     */
    ~Message() { delete[] msg; }

    /**
     * Message length getter
     * @return message length
     */
    [[nodiscard]] size_t get_msg_len() const noexcept { return msg_len; }

    /**
     * Message getter
     * @return message
     */
    [[nodiscard]] const unsigned char *get_msg() const noexcept { return msg; }

    /**
     * Message getter (hex)
     * @return message hex representation
     */
    [[nodiscard]] std::string get_msg_hex() const;

    /**
     * Message getter (ASCII)
     * @return message ASCII representation
     */
    [[nodiscard]] std::string get_msg_ascii() const { return {reinterpret_cast<char *>(msg)}; }
};
#endif // MESSAGE_H
