#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <string>

#include "../../../src/Server/Link/Link.hpp"

TEST_CASE("Link") {
    SECTION("Constructor") {
        Link link;
        REQUIRE(link.get_hostname().empty());
        REQUIRE(link.get_protocol() == HTTP);

        Link link2("aboba", FTP);
        REQUIRE(link2.get_hostname() == "aboba");
        REQUIRE(link2.get_protocol() == FTP);

        std::string aboba = "aboba";
        Link link3(aboba, FTP);
        REQUIRE(link3.get_hostname() == aboba);
        REQUIRE(link3.get_protocol() == FTP);
    }

    SECTION("Setters") {
        Link link;
        link.set_hostname("aboba").set_protocol(HTTP);
        REQUIRE(link.get_hostname() == "aboba");
        REQUIRE(link.get_protocol() == HTTP);

        std::string host = "mephi";
        link.set_hostname(host).set_protocol(FTP);
        REQUIRE(link.get_hostname() == host);
        REQUIRE(link.get_protocol() == FTP);
    }

    SECTION("Operators") {
        Link link1;
        Link link2;

        REQUIRE(link1 == link2);

        link1.set_protocol(FTP);
        REQUIRE_FALSE(link1 == link2);
    }
}
