#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <string>
#include <sstream>

#include "../../../src/Server/Message/Message.hpp"

TEST_CASE("Message") {
    auto msg = new byte[4];
    msg[0] = 'z';
    msg[1] = 'x';
    msg[2] = 'c';
    msg[3] = 0;

    SECTION("Constructors") {
        Message message;
        REQUIRE(message.get_msg()[0] == 0);
        REQUIRE(message.get_msg_len() == 0);

        Message message2(3, msg);
        REQUIRE(message2.get_msg_len() == 3);
        for (size_t i = 0; i < 4; ++i) {
            REQUIRE(message2.get_msg()[i] == msg[i]);
        }

        Message message3(message2);
        REQUIRE(message3.get_msg_len() == 3);
        for (size_t i = 0; i < 4; ++i) {
            REQUIRE(message3.get_msg()[i] == msg[i]);
        }

        Message message4(std::move(message2));
        REQUIRE(message4.get_msg_len() == 3);
        for (size_t i = 0; i < 4; ++i) {
            REQUIRE(message4.get_msg()[i] == msg[i]);
        }

        REQUIRE(message2.get_msg_len() == 0);
    }

    SECTION("Getters") {
        Message message(3, msg);

        REQUIRE(message.get_msg_ascii() == "zxc");
        REQUIRE(message.get_msg_hex() == "7a786300");
    }

    SECTION("Operators") {
        Message message2(3, msg);

        Message message3;
        message3 = message2;
        REQUIRE(message3.get_msg_len() == 3);
        for (size_t i = 0; i < 4; ++i) {
            REQUIRE(message3.get_msg()[i] == msg[i]);
        }

        Message message4;
        message4 = std::move(message2);
        REQUIRE(message4.get_msg_len() == 3);
        for (size_t i = 0; i < 4; ++i) {
            REQUIRE(message4.get_msg()[i] == msg[i]);
        }

        REQUIRE(message2.get_msg_len() == 0);

        Message message5(3, msg);
        Message message6(3, msg);
        Message message7;

        REQUIRE(message5 == message6);
        REQUIRE_FALSE(message5 == message7);
    }

    delete[] msg;
}
