#include <iostream>

#include "CPU/memory/RegisterBlock.h"

int main() {
    RegisterBlock rb(4);

    try {
        rb.write_register(1, 10);
        long long val = rb.read_register(1);
        rb.lock_reg(1);
        if (!rb.write_register(1, 15)) {
            std::cout << "Register is locked" << std::endl;
        }

        rb.unlock_reg(1);
        if (!rb.write_register(1, 15)) {
            std::cout << "Register is locked" << std::endl;
        }
        else {
            std::cout << "Register is unlocked" << std::endl;
        }

        std::cout << val << std::endl;
        rb.write_register(10, 16);
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}