#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "../../../src/Server/TransportTable/TransportTable.hpp"
#include "../../../src/Server/Packages/MailPackage.hpp"
#include "../../../src/Server/Packages/FilePackage.hpp"

TEST_CASE("TransportTable") {
    auto msg_str = new byte[2];
    msg_str[0] = 'Z';
    msg_str[1] = 0;

    Message msg(1, msg_str);
    std::string name = "username";

    std::shared_ptr<Package> ptr1 = std::make_shared<MailPackage>(
            MailPackage({"1.1.1.1", "2.2.2.2"},name, msg)
            );

    std::shared_ptr<Package> ptr2 = std::make_shared<FilePackage>(
            FilePackage({"1.1.1.1", "2.2.2.2"}, msg, {ASCII, CMD})
            );

    std::shared_ptr<Package> ptr3 = std::make_shared<FilePackage>(
            FilePackage({"2.2.2.2", "3.3.3.3"}, msg, {BIN, DATA})
            );

    std::shared_ptr<Package> ptr4 = nullptr;

    SECTION("Constructor") {
        TransportTable tbl;
        REQUIRE(tbl.empty());

        TransportTable tbl2;
        tbl2.add_package(ptr1);
        tbl2.add_package(ptr2);

        TransportTable tbl3(tbl2);
        REQUIRE(tbl3 == tbl2);

        TransportTable tbl4(std::move(tbl2));
        REQUIRE(tbl4 == tbl3);
        REQUIRE(tbl2.empty());
    }

    SECTION("Operators") {
        TransportTable tbl;
        REQUIRE(tbl.get_table().empty());

        TransportTable tbl2;
        tbl2.add_package(ptr1);
        tbl2.add_package(ptr2);

        TransportTable tbl3;
        tbl3 = tbl2;
        REQUIRE(tbl3 == tbl2);
        REQUIRE_FALSE(tbl2 == tbl);

        TransportTable tbl4;
        tbl4 = std::move(tbl2);
        REQUIRE(tbl4 == tbl3);
        REQUIRE(tbl2.empty());
    }

    SECTION("Methods") {
        TransportTable tbl2;
        REQUIRE_NOTHROW(tbl2.add_package(ptr1));
        REQUIRE_NOTHROW(tbl2.add_package(ptr2));
        REQUIRE_THROWS(tbl2.add_package(ptr4));

        REQUIRE(tbl2.find_package(ptr1->get_receiver(), ptr1->get_package_type()) == ptr1);
        REQUIRE(tbl2.find_package(ptr3->get_receiver(), ptr3->get_package_type()) == nullptr);
        REQUIRE_THROWS(tbl2.find_package("", ""));

        REQUIRE_NOTHROW(tbl2.drop_package(ptr1->get_receiver(), ptr1->get_package_type()));
        REQUIRE(tbl2.find_package(ptr1->get_receiver(), ptr1->get_package_type()) == nullptr);
        REQUIRE_NOTHROW(tbl2.drop_package(ptr3->get_receiver(), ptr3->get_package_type()));
    }

    delete[] msg_str;
}
