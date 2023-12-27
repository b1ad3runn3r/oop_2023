#include "Calculations.hpp"

void count_distrib(std::map<std::string, std::atomic<size_t>> &distribution,
                   std::multimap<table_key_t, std::shared_ptr<Package>>::iterator begin,
                   std::multimap<table_key_t, std::shared_ptr<Package>>::iterator end)
{
    for (auto iter = begin; iter != end; ++iter) {
        distribution[iter->second->get_package_type()] += 1;
    }
}

std::map<std::string, std::atomic<size_t>>
count_distrib_multithread(TransportTable& table) {
    std::map<std::string, std::atomic<size_t>> distribution;
    const auto table_size = table.get_table().size();
    size_t num_hardware_threads = std::thread::hardware_concurrency();
    auto num_threads = std::min(table.get_table().size(), num_hardware_threads);
    std::vector<std::thread> threads(num_threads);

    for (size_t i = 0; i < num_threads; ++i) {
        size_t start = i * table_size / num_threads;
        size_t end = start + table_size / num_threads;

        auto iter_start = std::next(table.get_table().begin(), start);
        auto iter_end = std::next(table.get_table().begin(), end);

        threads[i] = std::thread(count_distrib, std::ref(distribution), iter_start, iter_end);
    }

    for (auto &thread : threads) {
        thread.join();
    }

    return distribution;
}

void count_transmission(std::map<std::string, std::atomic<size_t>> &transmissions,
                        std::multimap<table_key_t, std::shared_ptr<Package>>::iterator begin,
                        std::multimap<table_key_t, std::shared_ptr<Package>>::iterator end)
{
    for (auto iter = begin; iter != end; ++iter) {
        transmissions[iter->second->get_sender()] += 1;
    }
}

std::map<std::string, std::atomic<size_t>>
count_transmission_mt(TransportTable& table) {
    std::map<std::string, std::atomic<size_t>> transmissions;

    const auto table_size = table.get_table().size();
    size_t num_hardware_threads = std::thread::hardware_concurrency();
    auto num_threads = std::min(table.get_table().size(), num_hardware_threads);
    std::vector<std::thread> threads(num_threads);

    for (size_t i = 0; i < num_threads; ++i) {
        size_t start = i * table_size / num_threads;
        size_t end = start + table_size / num_threads;

        auto iter_start = std::next(table.get_table().begin(), start);
        auto iter_end = std::next(table.get_table().begin(), end);

        threads[i] = std::thread(count_transmission, std::ref(transmissions), iter_start, iter_end);
    }

    for (auto &thread : threads) {
        thread.join();
    }

    return transmissions;
}
