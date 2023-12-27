#define CATCH_CONFIG_MAIN

#include <catch2/catch_test_macros.hpp>
#include <sstream>
#include <string>

#include "../../../src/Server/Packages/HypertextPackage.hpp"

TEST_CASE("HypertextPackage") {
    std::string ip_send = "1.1.1.1";
    std::string ip_recv = "2.2.2.2";
    send_recv_ip ips = {ip_send, ip_recv};

    auto msg_str = new byte[4];
    msg_str[0] = 'z';
    msg_str[1] = 'x';
    msg_str[2] = 'c';
    msg_str[3] = 0;

    Message msg(3, msg_str);

    auto links = new Link[2];
    links[0].set_hostname("aboba.ru").set_protocol(FTP);
    links[1].set_hostname("mephi.ru").set_protocol(HTTP);

    links_arr l_arr = {links, 2};

    payload_info info = {ASCII, DATA};
    payload_info info2 = {BIN, CMD};

    SECTION("Constructor") {
        HypertextPackage hp1(ips, msg, info, {nullptr, 0});
        REQUIRE(hp1.get_links() == nullptr);
        REQUIRE(hp1.get_links_size() == 0);

        HypertextPackage hp2(ips, msg, info, l_arr);
        REQUIRE(hp2.get_links_size() == 2);
        for (size_t i = 0; i < 2; ++i) {
            REQUIRE(hp2.get_links()[i] == links[i]);
        }
    }

    SECTION("Getters") {
        HypertextPackage hp1(ips, msg, info, {nullptr, 0});
        REQUIRE(hp1.get_package_type() == "HYPERTEXT");
        REQUIRE(hp1.get_code_type() == ASCII);
        REQUIRE(hp1.get_info_type() == DATA);
    }

    SECTION("Get Info") {
        HypertextPackage hp1(ips, msg, info, l_arr);
        std::string info1 = hp1.get_info();

        std::stringstream ss1;
        ss1 << hp1.get_package_type() << ';';
        ss1 << hp1.get_sender() << ';';
        ss1 << hp1.get_receiver() << ';';
        ss1 << "ASCII" << ';';
        ss1 << "DATA" << ';';
        ss1 << "[FTP,aboba.ru] [HTTP,mephi.ru] ;";
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
        ss1 << "[FTP,aboba.ru] [HTTP,mephi.ru] ;";
        ss2 << msg.get_msg_hex();

        REQUIRE(ss2.str() == info3);
    }

    delete[] msg_str;
    delete[] links;
}
