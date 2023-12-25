#ifndef ENUMS_HPP
#define ENUMS_HPP

typedef unsigned char byte;

enum code_t {
    ASCII,
    BIN
};

enum info_t {
    CMD,
    DATA
};

enum proto_t {
    FTP,
    HTTP
};

struct payload_info {
    code_t code_type;
    info_t info_type;
};

struct send_recv_ip {
    std::string sender;
    std::string receiver;
};

#endif // ENUMS_HPP
