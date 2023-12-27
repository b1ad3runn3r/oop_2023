#include <iostream>
#include <vector>
#include <map>
#include <random>
#include <chrono>
#include <thread>
#include <format>

#include "Server/Packages/Package.hpp"
#include "Server/Packages/MailPackage.hpp"
#include "Server/Packages/FilePackage.hpp"
#include "Server/Packages/HypertextPackage.hpp"
#include "Server/TransportTable/TransportTable.hpp"
#include "Server/Message/Message.hpp"

void ccount(std::map<std::string, std::atomic<size_t>>& distrib,
            std::multimap<table_key_t, std::shared_ptr<Package>>::iterator begin,
            std::multimap<table_key_t, std::shared_ptr<Package>>::iterator end) {

    for (auto iter = begin; iter != end; ++iter) {
        distrib[iter->second->get_package_type()] += 1;
    }
}

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

    TransportTable table;
    std::map<std::string, std::atomic<size_t>> distribution;
    distribution["MAIL"] = 0;
    distribution["FILE"] = 0;
    distribution["HYPERTEXT"] = 0;

    std::random_device rnd;
    std::mt19937_64 rng(rnd());
    std::uniform_int_distribution<size_t> uni(1, 4);

    // Generate
    for (size_t i = 0; i < 1000000; ++i) {
        auto rand_num = uni(rng);
        switch (rand_num % 3) {
            case 0:
                table.add_package(std::make_shared<MailPackage>(
                        MailPackage(
                                {"1.1.1.1", "2.2.2.2"} ,
                                name,
                                msg)
                ));
                break;

            case 1:
                table.add_package(std::make_shared<FilePackage>(
                        FilePackage(
                                {"1.1.1.1", "2.2.2.2"} ,
                                msg,
                                {ASCII, DATA})
                ));
                break;

            case 2:
                table.add_package(std::make_shared<HypertextPackage>(
                        HypertextPackage(
                                {"1.1.1.1", "2.2.2.2"},
                                msg,
                                {ASCII, DATA},
                                {nullptr, 0})
                ));
                break;
        }
    }
    const auto table_size = table.get_table().size();
    std::cout << "Table size: " << table_size << std::endl << std::endl;

    // One threaded
    auto one_iter_begin = table.get_table().begin();
    auto one_iter_end = table.get_table().end();

    auto one_begin = std::chrono::steady_clock::now();
    ccount(distribution, one_iter_begin, one_iter_end);
    auto one_end = std::chrono::steady_clock::now();

    auto one_duration = std::chrono::duration_cast<std::chrono::microseconds>(one_end - one_begin).count();
    std::cout << "One threaded result: " << one_duration << "us" << std::endl;
    for (const auto &iter : distribution) {
        std::cout << std::format("{} found {} times!", iter.first, iter.second.load()) << std::endl;
    }

    std::cout << std::endl;

    // Multi-threaded
    distribution["MAIL"] = 0;
    distribution["FILE"] = 0;
    distribution["HYPERTEXT"] = 0;

    size_t hardware = std::thread::hardware_concurrency();
    auto num_threads = std::min(hardware, table.get_table().size());

    std::vector<std::thread> threads(num_threads);
    for (size_t i = 0; i < num_threads; ++i) {
        size_t start = i * table_size / num_threads;
        size_t end = start + table_size / num_threads;

        auto iter_start = std::next(table.get_table().begin(), start);
        auto iter_end = std::next(table.get_table().begin(), end);

        threads[i] = std::thread(ccount, std::ref(distribution), iter_start, iter_end);
    }

    auto mt_begin = std::chrono::steady_clock::now();
    for (auto &thread : threads) {
        thread.join();
    }
    auto mt_end = std::chrono::steady_clock::now();
    auto mt_duration = std::chrono::duration_cast<std::chrono::microseconds>(mt_end - mt_begin).count();
    std::cout << "Multi-threaded result: " << mt_duration << "us" << std::endl;
    for (const auto &iter : distribution) {
        std::cout << std::format("{} found {} times!", iter.first, iter.second.load()) << std::endl;
    }

    delete[] msg_str;
    return 0;
}
