#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "../../src/Vector/VectorIterator.h"
#include "../../src/Vector/Vector.h"

static_assert(std::contiguous_iterator<VectorIterator<int, true>>);
static_assert(std::contiguous_iterator<VectorIterator<int, false>>);

TEST_CASE("Vector Constructors") {
    SECTION("Default constructor") {
        Vector<long> vec;
        REQUIRE(vec.empty());
        REQUIRE(vec.capacity() == 0);
    }

    SECTION("From size") {
        Vector<long> vec(10);
        REQUIRE(vec.empty());
        REQUIRE(vec.capacity() == 10);
    }

    SECTION("Copy constructor") {
        Vector<long> vec1{1,2,3,4};
        Vector<long> vec2{vec1};

        REQUIRE(vec1 == vec2);
    }

    SECTION("Move constructor") {
        Vector<long> vec1{1,2,3,4};
        Vector<long> vec2{ std::move(vec1) };

        REQUIRE(vec1.empty());
        REQUIRE(vec2.size() == 4);
    }

    SECTION("From size and default value") {
        Vector<long> vec1(4,4);

        REQUIRE(vec1.size() == 4);
    }

    SECTION("From initializer list") {
        Vector<long> vec1 = {1,2,3,4};

        REQUIRE(vec1.size() == 4);
    }

    SECTION("From iterators") {
        Vector<long> vec1{1,2,3,4,5,6,7};
        Vector<long> vec2{vec1.begin(), vec1.end()};

        REQUIRE(vec1 == vec2);
    }
}

TEST_CASE("Vector methods") {
    SECTION("at() method") {
        Vector<long> vec1{1,2,3};

        REQUIRE(vec1.at(1) == 2);
        REQUIRE_THROWS(vec1.at(-1));

        const Vector<long> vec2{1,2,3,4};
        REQUIRE(vec2.at(2) == 3);
        REQUIRE_THROWS(vec2.at(-1));
    }

    SECTION("emplace() method") {
        Vector<long> vec1{1,2,3};
        vec1.emplace(vec1.cbegin() + 1, 0);

        REQUIRE(vec1[1] == 0);
    }

    SECTION("insert() method") {
        Vector<long> vec1{1,2,3};
        vec1.insert(vec1.cbegin(), 3, 1);

        REQUIRE(vec1 == Vector<long>{1,1,1,1,2,3});
    }

    SECTION("erase() method") {
        Vector<long> vec1{1,2,3,4};
        vec1.erase(vec1.cbegin() + 1);

        REQUIRE(vec1 == Vector<long>{1,3,4});

        Vector<long> vec2{1,2,3,4};
        vec2.erase(vec2.begin(), vec2.end());

        REQUIRE(vec2.empty());
    }

    SECTION("assign() method") {
        Vector<long> vec1{1,2,3,4};
        Vector<long> vec2;

        vec2.assign(vec1.begin(), vec1.end());
        REQUIRE(vec2 == vec1);

        vec1.assign({4,3,2,1});
        REQUIRE(vec1 == Vector<long>{4,3,2,1});

        Vector<long> vec3{1,1,1};
        vec3.assign(3,3);
        REQUIRE(vec3 == Vector<long>{3,3,3});
    }

    SECTION("push_back() method") {
        Vector<long> vec1{1,2,3};
        vec1.push_back(4);

        REQUIRE(vec1 == Vector<long>{1,2,3,4});
    }

    SECTION("resize() method") {
        Vector<long> vec1{1,2,3,4,5};
        vec1.resize(2);

        REQUIRE(vec1.size() == 2);
        REQUIRE(vec1.capacity() == 2);
        REQUIRE(vec1 == Vector<long>{1,2});
    }

    SECTION("max_size() method") {
        Vector<long> vec1;

        REQUIRE(vec1.max_size() == std::numeric_limits<size_t>::max());
    }
}

TEST_CASE("Vector operators") {
    SECTION("Copy =") {
        const Vector<long> vec1{1,2};
        Vector<long> vec2;
        vec2 = vec1;

        REQUIRE(vec1 == vec2);
    }

    SECTION("Move =") {
        Vector<long> vec1{1,2};
        Vector<long> vec2;
        vec2 = std::move(vec1);

        REQUIRE(vec1.empty());
        REQUIRE(vec2 == Vector<long>{1,2});
    }

    SECTION("Initializer list") {
        Vector<long> vec1;
        vec1 = {1,2,3,4,5};

        REQUIRE(vec1.size() == 5);
        REQUIRE(vec1 == Vector<long>{1,2,3,4,5});
    }

    SECTION("[] Operator") {
        Vector<long> vec1{1,2,3,4};

        REQUIRE(vec1[1] == 2);
    }
}

TEST_CASE("STL functions") {
    SECTION("std::find() function") {
        Vector<long> vec1{1,2,3,4};

        REQUIRE(std::find(vec1.begin(), vec1.end(), 1) == vec1.begin());
        REQUIRE(std::find(vec1.begin(), vec1.end(), 4) == vec1.begin() + vec1.size() - 1);
        REQUIRE(std::find(vec1.begin(), vec1.end(), 5) == std::end(vec1));
    }
}

TEST_CASE("VectorIterator constructors") {
    long *arr = new long[3];
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;

    SECTION("Default constructor") {
        VectorIterator<long, false> iter;
        REQUIRE(iter.operator->() == nullptr);
    }

    SECTION("Constructor from pointer") {
        VectorIterator<long, false> iter(arr);

        REQUIRE(iter.operator->() == arr);
    }

    SECTION("Copy constructor") {
        VectorIterator<long, false> iter1(arr);
        VectorIterator<long, false> iter2(iter1);

        REQUIRE(iter1 == iter2);
    }

    SECTION("Move constructor") {
        VectorIterator<long, false> iter1(arr);
        VectorIterator<long, true> iter2(std::move(iter1));

        REQUIRE(iter2.operator->() == arr);
        REQUIRE(iter1.operator->() == nullptr);
    }

    delete[] arr;
}

TEST_CASE("VectorIterator operators") {
    long *arr = new long[3];
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;

    SECTION("Copy assignment") {
        VectorIterator<long, false> iter1(arr);
        VectorIterator<long, true> iter2;
        iter2 = iter1;

        REQUIRE(iter2 == iter1);
    }

    SECTION("Move assignment") {
        VectorIterator<long, false> iter1(arr);
        VectorIterator<long, true> iter2;
        iter2 = std::move(iter1);

        REQUIRE(iter2.operator->() == arr);
        REQUIRE(iter1.operator->() == nullptr);
    }

    SECTION("+= operator") {
        VectorIterator<long, false> iter1(arr);
        iter1 += 1;

        REQUIRE(*iter1 == 2);
    }

    SECTION("-= operator") {
        VectorIterator<long, false> iter1(arr + 1);
        iter1 -= 1;

        REQUIRE(*iter1 == 1);
    }

    SECTION("[] operator") {
        VectorIterator<long, false> iter1(arr);

        REQUIRE(iter1[0] == 1);
    }

    SECTION("++ operator") {
        VectorIterator<long, false> iter1(arr);
        ++iter1;

        REQUIRE(iter1.operator->() == arr + 1);
    }

    SECTION("-- operator") {
        VectorIterator<long, false> iter1(arr + 1);
        --iter1;

        REQUIRE(iter1.operator->() == arr);
    }

    SECTION("+ operator") {
        VectorIterator<long, false> iter1(arr);

        REQUIRE((iter1 + 1).operator->() == arr + 1);
    }

    SECTION("- operator") {
        VectorIterator<long, false> iter1(arr + 1);
        VectorIterator<long, false> iter2(arr + 2);

        REQUIRE((iter1 - 1).operator->() == arr);
        REQUIRE(iter2 - iter1 == 1);
    }

    SECTION("> operator") {
        VectorIterator<long, false> iter1(arr);
        VectorIterator<long, false> iter2(arr);
        VectorIterator<long, false> iter3(arr + 1);

        REQUIRE(iter3 > iter1);
        REQUIRE_FALSE(iter1 > iter2);
    }

    SECTION(">= operator") {
        VectorIterator<long, false> iter1(arr);
        VectorIterator<long, false> iter2(arr);
        VectorIterator<long, false> iter3(arr + 1);

        REQUIRE(iter1 >= iter2);
        REQUIRE(iter3 >= iter1);
    }

    SECTION("< operator") {
        VectorIterator<long, false> iter1(arr);
        VectorIterator<long, false> iter2(arr);
        VectorIterator<long, false> iter3(arr + 1);

        REQUIRE_FALSE(iter1 < iter2);
        REQUIRE(iter2 < iter3);
    }

    SECTION("<= operator") {
        VectorIterator<long, false> iter1(arr);
        VectorIterator<long, false> iter2(arr);
        VectorIterator<long, false> iter3(arr + 1);

        REQUIRE(iter1 <= iter2);
        REQUIRE(iter2 <= iter3);
    }

    SECTION("== operator") {
        VectorIterator<long, false> iter1(arr);
        VectorIterator<long, false> iter2(arr);

        REQUIRE(iter1 == iter2);
    }

    delete[] arr;
}
