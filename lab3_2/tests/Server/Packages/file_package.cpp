#define CATCH_CONFIG_MAIN

#include <catch2/catch_test_macros.hpp>
#include <sstream>
#include <string>

#include "../../../src/Server/Packages/FilePackage.hpp"
#include "../../../src/Server/Packages/HypertextPackage.hpp"

TEST_CASE("FilePackage") {
    std::string ip_send = "1.1.1.1";
    std::string ip_recv = "2.2.2.2";
    send_recv_ip ips = {ip_send, ip_recv};

    payload_info info = {ASCII, DATA};
    payload_info info2 = {BIN, CMD};

    auto msg_str = new byte[4];
    msg_str[0] = 'z';
    msg_str[1] = 'x';
    msg_str[2] = 'c';
    msg_str[3] = 0;

    Message msg(3, msg_str);

    SECTION("Constructor") {
        REQUIRE_NOTHROW(FilePackage(ips, msg, info));
        REQUIRE_THROWS(FilePackage({"", ""}, msg, info));
    }

    SECTION("Getters") {
        FilePackage fp(ips, msg, info);

        REQUIRE(fp.get_package_type() == "FILE");
        REQUIRE(fp.get_info_type() == DATA);
        REQUIRE(fp.get_code_type() == ASCII);
    }

    SECTION("Get Info") {
        FilePackage fp1(ips, msg, info);
        std::string info1 = fp1.get_info();

        std::stringstream ss1;
        ss1 << fp1.get_package_type() << ';';
        ss1 << fp1.get_sender() << ';';
        ss1 << fp1.get_receiver() << ';';
        ss1 << "ASCII" << ';';
        ss1 << "DATA" << ';';
        ss1 << msg.get_msg_ascii();

        REQUIRE(ss1.str() == info1);

        FilePackage fp2(ips, msg, info2);
        std::string info3 = fp2.get_info();

        std::stringstream ss2;
        ss2 << fp2.get_package_type() << ';';
        ss2 << fp2.get_sender() << ';';
        ss2 << fp2.get_receiver() << ';';
        ss2 << "BIN" << ';';
        ss2 << "CMD" << ';';
        ss2 << msg.get_msg_hex();

        REQUIRE(ss2.str() == info3);
    }

    SECTION("Conversion to HypertextPackage") {
        FilePackage fp(ips, msg, info);

        HypertextPackage hp = fp.convert_to_hypertext();
        REQUIRE(hp.get_package_type() == "HYPERTEXT");
        REQUIRE(hp.get_links() == nullptr);
        REQUIRE(hp.get_links_size() == 0);
    }

    delete[] msg_str;
}
