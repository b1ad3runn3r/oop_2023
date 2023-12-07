#ifndef _VECTOR_H
#define _VECTOR_H

#include "VectorIterator.h"
#include <algorithm>

template <typename T>
class Vector {
public:
    typedef VectorIterator<T, false> iterator;
    typedef VectorIterator<T, true> const_iterator;
    typedef T value_type;
    typedef T &reference;
    typedef const T &const_reference;
    typedef std::ptrdiff_t difference_type;
    typedef size_t size_type;

    Vector() noexcept : container(nullptr), cur_n(0), max_n(0) {};

    explicit Vector(size_type size)
    requires std::default_initializable<T>
    : container(new T[size]), cur_n(0), max_n(size) {};

    Vector(const Vector &o) : Vector() {
        insert(cend(), o.cbegin(), o.cend());
        max_n = o.max_n;
    }

    Vector(Vector &&o) noexcept : Vector() {
        swap(o);
    }

    Vector(size_type n, const T &t) : Vector() {
        insert(cend(), n, t);
        max_n = n;
    }

    template <std::input_iterator I>
    Vector(I i1, I i2)
    requires std::constructible_from<T, std::iter_reference_t<I>>
    : Vector()
    {
        insert(cend(), i1, i2);
        max_n = i2 - i1;
    }

    Vector(std::initializer_list<T> il)
    requires std::move_constructible<T>
    : Vector()
    {
        insert(cend(), std::move(il));
        max_n = il.size();
    }

    ~Vector() {
        delete[] container;
    }

    Vector &operator=(const Vector &o) {
        if (this != &o) {
            assign(o.cbegin(), o.cend());
            max_n = o.max_n;
        }

        return *this;
    }

    Vector &operator=(Vector &&o) noexcept {
        swap(o);
        return *this;
    }

    Vector &operator=(std::initializer_list<T> il) {
        assign(std::move(il));
        max_n = il.size();
        return *this;
    }

    reference operator[] (size_type idx) noexcept {
        return container[idx];
    }

    const_reference operator[] (size_type idx) const noexcept {
        return container[idx];
    }

    reference at(size_type idx) {
        if (idx >= cur_n) {
            throw std::invalid_argument("Index is greater than size");
        }

        return (*this)[idx];
    }

    const_reference at(size_type idx) const {
        if (idx >= cur_n) {
            throw std::invalid_argument("Index is greater than size");
        }

        return (*this)[idx];
    }

    iterator begin() noexcept { return iterator(container); }
    iterator end() noexcept { return iterator(container + cur_n); }

    const_iterator begin() const noexcept { return iterator(container); }
    const_iterator end() const noexcept { return iterator(container + cur_n); }

    const_iterator cbegin() const noexcept { return const_iterator(container); }
    const_iterator cend() const noexcept { return const_iterator(container + cur_n); }

    bool operator==(const Vector &o) const noexcept {
        return cur_n == o.cur_n && std::equal(begin(), begin() + cur_n, o.begin(), o.begin() + o.cur_n);
    }

    void swap(Vector &o) noexcept {
        std::swap(container, o.container);
        std::swap(cur_n, o.cur_n);
        std::swap(max_n, o.max_n);
    }

    [[nodiscard]] size_type size() const noexcept { return cur_n; }

    [[nodiscard]] size_type max_size() const noexcept { return std::numeric_limits<size_type>::max(); }

    [[nodiscard]] size_type capacity() const noexcept { return max_n; }

    [[nodiscard]] bool empty() const noexcept { return cur_n == 0; }

    template <typename... Args>
    iterator emplace(const_iterator p, Args &&...args)
    requires std::constructible_from<T, Args...>
    {
        size_type dist = cend() - p;

        if (capacity() <= size()) {
            resize(capacity() + 1);
        }

        iterator i_end = end();
        while (i_end != end() - dist) {
            *i_end = std::move(*(i_end - 1));
            --i_end;
        }

        *i_end = value_type(std::forward<Args>(args)...);
        ++cur_n;

        return i_end + 1;
    }

    iterator insert(const_iterator p, const T &t) { return emplace(p, t); }
    iterator insert(const_iterator p, T &&t) { return emplace(p, std::move(t)); }

    const_iterator insert(const_iterator p, size_type n, const T &t)
    requires std::copy_constructible<T>
    {
        if (n == 0) {
            return p;
        }

        const_iterator prev(p - 1);
        iterator tmp = end() - (cend() - p);

        try {
            for (size_type i = 0; i < n; ++i) {
                tmp = insert(tmp, t);
            }
        }
        catch (...) {
            erase(++prev, p);
            throw ;
        }

        return prev;
    }

    template <std::input_iterator I>
    const_iterator insert(const_iterator p, I i_start, I i_end) {
        if (i_start == i_end) {
            return p;
        }

        const_iterator prev(p - 1);
        iterator it = begin() + (p - begin());

        try {
            while (i_start != i_end) {
                it = insert(it, *i_start);
                ++i_start;
            }
        }
        catch (...) {
            erase(++prev, it);
            throw ;
        }

        return prev;
    }

    const_iterator insert(const_iterator p, std::initializer_list<T> il)
    requires std::move_constructible<T>
    {
        return insert(p, std::move_iterator(il.begin()), std::move_iterator(il.end()));
    }

    iterator erase(const_iterator it) {
        if (size() == 0) {
            return end();
        }

        size_type distance = it - begin();
        for (auto i = begin() + distance; i != end() - 1; ++i) {
            *i = std::move(*(i + 1));
        }

        --cur_n;
        return begin() + distance;
    }

    iterator erase(const_iterator it1, const_iterator it2) {
        iterator i_start1 = begin() + (it1 - cbegin());
        iterator i_start2 = begin() + (it2 - cbegin());

        while (i_start2 - i_start1 > 0) {
            i_start1 = erase(i_start1);
            --i_start2;
        }

        return i_start2;
    }

    template<std::forward_iterator I>
    void assign(I i1, I i2) {
        if (!empty()) {
            erase(cbegin(), cend());
        }

        insert(cend(), i1, i2);
    }

    void assign(std::initializer_list<T> il) {
        if (!empty()) {
            erase(begin(), end());
        }

        insert(end(), std::move(il));
    }

    void assign(size_type n, const T &t) {
        if (!empty()) {
            erase(begin(), end());
        }

        insert(end(), n, t);
    }

    void push_back(const T &t) {
        insert(end(), t);
    }

    void push_back(T &&t) {
        insert(end(), std::move(t));
    }

    void resize(long long n) {
        if (n < 0) {
            throw std::invalid_argument("New size can't be < 0");
        }

        if (n == max_n) {
            return ;
        }

        long long to_copy = (n < size()) ? n : size();
        // long long to_copy = std::min(n, size());
        T *new_container = new T[n];
        std::copy(container, container + to_copy, new_container);

        delete[] container;
        container = new_container;
        max_n = n;
        cur_n = to_copy;
    }

private:
    T* container;
    size_type cur_n;
    size_type max_n;
};

#endif // _VECTOR_H
