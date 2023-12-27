#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <sstream>
#include <string>

#include "../../../src/Server/Packages/MailPackage.hpp"
#include "../../../src/Server/Packages/FilePackage.hpp"

TEST_CASE("MailPackage") {
    std::string ip_send = "1.1.1.1";
    std::string ip_recv = "2.2.2.2";
    send_recv_ip ips = {ip_send, ip_recv};
    std::string username = "aboba";

    auto msg_str = new byte[4];
    msg_str[0] = 'z';
    msg_str[1] = 'x';
    msg_str[2] = 'c';
    msg_str[3] = 0;

    Message msg(3, msg_str);

    SECTION("Constructor") {
        REQUIRE_NOTHROW(MailPackage(ips, username, msg));

        std::string username2;
        std::string username3 = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
        REQUIRE_THROWS(MailPackage(ips, username2, msg));
        REQUIRE_THROWS(MailPackage(ips, username3, msg));
        REQUIRE_THROWS(MailPackage({"", ""}, username, msg));
    }

    SECTION("Getters") {
        MailPackage mail_package(ips, username, msg);

        REQUIRE(mail_package.get_username() == "aboba");
        REQUIRE(mail_package.get_package_type() == "MAIL");
        auto sender = mail_package.get_sender();
        for (size_t i = 0; i < 4; ++i) {
            REQUIRE(sender[i] == ip_send[i]);
        }

        auto receiver = mail_package.get_receiver();
        for (size_t i = 0; i < 4; ++i) {
            REQUIRE(receiver[i] == ip_recv[i]);
        }

        REQUIRE(mail_package.get_sender() == "1.1.1.1");
        REQUIRE(mail_package.get_receiver() == "2.2.2.2");
    }

    /*SECTION("Operators") {
        MailPackage p1(ips, username, msg);
        MailPackage p2(ips, username, msg);

        REQUIRE(p1 == p2);

        std::string username2 = "username";
        MailPackage p3(ips, username2, msg);
        REQUIRE_FALSE(p1 == p2);
    }*/

    SECTION("Get Info") {
        MailPackage mail_package(ips, username, msg);
        std::string info = mail_package.get_info();

        std::stringstream ss;
        ss << "sender: " << mail_package.get_sender() << '\n';
        ss << "receiver: " << mail_package.get_receiver() << '\n';
        ss << "user: " << mail_package.get_username() << '\n';
        ss << "message: ";
        ss << std::hex;
        for (int i = 0; i < 4; i++) {
            ss << static_cast<int>(msg.get_msg()[i]);
        }
        ss << "0";

        REQUIRE(ss.str() == info);
    }

    SECTION("Conversion to FilePackage") {
        MailPackage mail_package(ips, username, msg);
        FilePackage fp = mail_package.convert_to_file();

        REQUIRE(fp.get_package_type() == "FILE");
        REQUIRE(fp.get_code_type() == ASCII);
        REQUIRE(fp.get_info_type() == DATA);
    }

    delete[] msg_str;
}
