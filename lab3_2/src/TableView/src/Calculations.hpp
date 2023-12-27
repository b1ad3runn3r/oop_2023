#ifndef CALCULATIONS_HPP
#define CALCULATIONS_HPP

#include "../../Server/TransportTable/TransportTable.hpp"
#include <thread>
#include <map>
#include <memory>
#include <string>
#include <set>

void count_distrib(std::map<std::string, std::atomic<size_t>> &distribution,
                   std::multimap<table_key_t, std::shared_ptr<Package>>::iterator begin,
                   std::multimap<table_key_t, std::shared_ptr<Package>>::iterator end);


std::map<std::string, std::atomic<size_t>>
count_distrib_multithread(TransportTable& table);

void count_transmission(std::map<std::string, std::atomic<size_t>> &transmissions,
                        std::multimap<table_key_t, std::shared_ptr<Package>>::iterator begin,
                        std::multimap<table_key_t, std::shared_ptr<Package>>::iterator end);

std::map<std::string, std::atomic<size_t>>
count_transmission_mt(TransportTable& table);

#endif // CALCULATIONS_HPP
