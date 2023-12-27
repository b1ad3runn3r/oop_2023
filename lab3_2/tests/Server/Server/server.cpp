#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "../../../src/Server/Server/Server.hpp"
#include "../../../src/Server/Packages/MailPackage.hpp"

TEST_CASE("Server") {
    auto msg_str = new byte[2];
    msg_str[0] = 'Z';
    msg_str[1] = 0;

    Message msg(1, msg_str);
    std::string name = "username";

    std::shared_ptr<Package> ptr1 = std::make_shared<MailPackage>(
            MailPackage({"1.1.1.1", "2.2.2.2"},name, msg)
    );

    TransportTable tbl;
    tbl.add_package(ptr1);

    SECTION("Constructor") {
        REQUIRE_THROWS(Server("", ""));
        REQUIRE_THROWS(Server("", "", tbl));

        REQUIRE_NOTHROW(Server("mephi.ru", "1.1.1.1"));
        REQUIRE_NOTHROW(Server("mephi.ru", "1.1.1.1", tbl));

        Server server("mephi.ru", "1.1.1.1", tbl);
        Server server2(server);

        REQUIRE(server2.get_hostname() == "mephi.ru");
        REQUIRE(server2.get_ip() == "1.1.1.1");
        REQUIRE(server2.get_table() == tbl);

        Server server3(std::move(server));

        REQUIRE(server3.get_hostname() == "mephi.ru");
        REQUIRE(server3.get_ip() == "1.1.1.1");
        REQUIRE(server3.get_table() == tbl);
    }

    SECTION("Operators") {
        Server server("mephi.ru", "1.1.1.1", tbl);
        Server server2("aboba.ru", "2.2.2.2", tbl);
        server2 = server;

        REQUIRE(server2.get_hostname() == "mephi.ru");
        REQUIRE(server2.get_ip() == "1.1.1.1");
        REQUIRE(server2.get_table() == tbl);

        Server server3("aboba.ru", "2.2.2.2", tbl);
        server3 = std::move(server);

        REQUIRE(server3.get_hostname() == "mephi.ru");
        REQUIRE(server3.get_ip() == "1.1.1.1");
        REQUIRE(server3.get_table() == tbl);
    }

    delete[] msg_str;
}
