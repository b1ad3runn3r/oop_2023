#include <iostream>
#include <sstream>

#include "Server/Packages/Package.hpp"
#include "Server/Packages/MailPackage.hpp"
#include "Server/TransportTable/TransportTable.hpp"
#include "Server/Message/Message.hpp"

int main() {
    auto msg_str = new byte[2];
    msg_str[0] = 'Z';
    msg_str[1] = 0;

    Message msg(1, msg_str);
    std::string name = "username";

    TransportTable tbl;
    std::shared_ptr<Package> ptr1 = std::make_shared<MailPackage>(
            MailPackage({"1.1.1.1", "2.2.2.2"} ,name, msg));

    std::shared_ptr<Package> ptr2 = std::make_shared<MailPackage>(
            MailPackage({"1.1.1.1", "2.2.2.2"} ,name, msg));

    std::cout << ptr1->get_info() << std::endl;
    std::cout << ptr2->get_info() << std::endl;

    TransportTable table;
    table.add_package(ptr1);
    table.add_package(ptr2);

    std::ostringstream ss;
    ss << table;

    std::cout << ss.str() << std::endl;

    delete[] msg_str;

    return 0;
}
