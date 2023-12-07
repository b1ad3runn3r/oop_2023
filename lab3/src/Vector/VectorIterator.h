#ifndef _VECTOR_ITERATOR_H
#define _VECTOR_ITERATOR_H
#include <algorithm>
#include <limits>
#include <stdexcept>

template <typename T, bool is_const>
class VectorIterator {

    friend VectorIterator<T, !is_const>;

public:
    typedef T value_type;
    typedef std::conditional_t<is_const, const T, T> *pointer;
    typedef std::conditional_t<is_const, const T, T> &reference;
    typedef std::ptrdiff_t difference_type;
    typedef std::contiguous_iterator_tag iterator_category;

    VectorIterator() noexcept : ptr(nullptr) {};
    explicit VectorIterator(pointer pptr) : ptr(pptr) {};

    template <bool other_const>
    VectorIterator(VectorIterator<T, other_const> &o) noexcept
    requires(is_const >= other_const) : ptr(o.ptr) {};

    template <bool other_const>
    VectorIterator(VectorIterator<T, other_const> &&o) noexcept
    requires(is_const >= other_const) : ptr(o.ptr)
    {
        o.ptr = nullptr;
    }

    template <bool other_const>
    VectorIterator &operator=(VectorIterator<T, other_const> &o) noexcept
    requires(is_const >= other_const)
    {
        ptr = o.ptr ;
        return *this;
    }

    template <bool other_const>
    VectorIterator &operator=(VectorIterator<T, other_const> &&o) noexcept
    requires(is_const >= other_const)
    {
        ptr = o.ptr;
        o.ptr = nullptr;
        return *this;
    }

    VectorIterator &operator+=(difference_type distance) noexcept {
        ptr += distance;
        return *this;
    }

    VectorIterator &operator-=(difference_type distance) noexcept {
        ptr -= distance;
        return *this;
    }

    reference operator*() const noexcept { return *ptr; }
    pointer operator->() const noexcept { return ptr; }
    reference operator[](size_t idx) const noexcept { return ptr[idx]; }

    VectorIterator &operator++() noexcept {
        ++ptr;
        return *this;
    }

    VectorIterator &operator--() noexcept {
        --ptr;
        return *this;
    }

    VectorIterator operator++(int) noexcept {
        VectorIterator temp(*this);
        ++*this;
        return temp;
    }

    VectorIterator operator--(int) noexcept {
        VectorIterator temp(*this);
        --*this;
        return temp;
    }

    VectorIterator operator+(difference_type distance) const noexcept {
        return VectorIterator(ptr + distance);
    }

    VectorIterator operator-(difference_type distance) const noexcept {
        return VectorIterator(ptr - distance);
    }

    difference_type operator-(const VectorIterator iter) const noexcept {
        return ptr - iter.ptr;
    }

    friend VectorIterator operator+(difference_type distance, const VectorIterator iter) {
        return VectorIterator(iter.ptr + distance);
    }

    friend VectorIterator operator-(difference_type distance, const VectorIterator iter) {
        return VectorIterator(iter.ptr - distance);
    }

    template <bool other_const>
    bool operator==(const VectorIterator<T, other_const> &o) const noexcept {
        return ptr == o.ptr;
    }

    bool operator>(const VectorIterator iter) const noexcept {
        return ptr > iter.ptr;
    }

    bool operator>=(const VectorIterator iter) const noexcept {
        return ptr >= iter.ptr;
    }

    bool operator<(const VectorIterator iter) const noexcept {
        return ptr < iter.ptr;
    }

    bool operator<=(const VectorIterator iter) const noexcept {
        return ptr <= iter.ptr;
    }

private:
    pointer ptr;
};


#endif //_VECTOR_ITERATOR_H
