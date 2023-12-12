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

    /**
     * @brief Vector constructor
     *
     * Default constructor for Vector
     */
    Vector() noexcept : container(nullptr), cur_n(0), max_n(0) {};

    /**
     * @brief Vector constructor from size
     *
     * Vector constructor from size
     * @param size Size of vector
     */
    explicit Vector(size_type size)
    requires std::default_initializable<T>
    : container(new T[size]), cur_n(0), max_n(size) {};

    /**
     * @brief Copy constructor
     *
     * Copy constructor for Vector
     *
     * @param o const reference to other Vector
     */
    Vector(const Vector &o) : Vector() {
        insert(cend(), o.cbegin(), o.cend());
        //max_n = o.max_n;
    }

    /**
     * @brief Move constructor
     *
     * Move constructor for Vector class
     *
     * @param o rvalue to other Vector
     */
    Vector(Vector &&o) noexcept : Vector() {
        swap(o);
    }

    /**
     * @brief Constructor from size and value
     *
     * Constructor for Vector class from size and default value
     *
     * @param n size of new vector
     * @param t value to initialize
     */
    Vector(size_type n, const T &t) : Vector() {
        insert(cend(), n, t);
        //max_n = n;
    }

    /**
     * @brief Start / end constructor
     *
     * Constructor for Vector class from start and end iterator
     *
     * @tparam I Input iterator
     * @param i1 Start iterator
     * @param i2 End iterator
     */
    template <std::input_iterator I>
    Vector(I i1, I i2)
    requires std::constructible_from<T, std::iter_reference_t<I>>
    : Vector()
    {
        insert(cend(), i1, i2);
        //max_n = i2 - i1;
    }

    /**
     * @brief Constructor from initializer_list
     *
     * Constructor for Vector from initializer_list
     *
     * @param il std::initializer_list<T>
     */
    Vector(std::initializer_list<T> il)
    requires std::move_constructible<T>
    : Vector()
    {
        insert(cend(), std::move(il));
        //max_n = il.size();
    }

    /**
     * @brief Vector destructor
     * Vector destructor
     */
    ~Vector() {
        delete[] container;
    }

    /**
     * @brief Copy assignment
     *
     * Copy assignment operator
     *
     * @param o lvalue to other Vector
     * @return reference to itself
     */
    Vector &operator=(const Vector &o) {
        if (this != &o) {
            assign(o.cbegin(), o.cend());
            //max_n = o.max_n;
        }

        return *this;
    }

    /**
     * @brief Move assignment
     *
     * Move assignment operator
     *
     * @param o rvalue to other Vector
     * @return reference to itself
     */
    Vector &operator=(Vector &&o) noexcept {
        swap(o);
        return *this;
    }

    /**
     * @brief Initializer assignment
     *
     * Assigment operator from std::initializer_list<T>
     *
     * @param il std::initializer_list<T>
     * @return reference to itself
     */
    Vector &operator=(std::initializer_list<T> il) {
        assign(std::move(il));
        //max_n = il.size();
        return *this;
    }

    /**
     * @brief Index operator
     *
     * Square braces operator for vector
     *
     * @param idx index of element
     * @return reference to element by index
     */
    reference operator[] (size_type idx) noexcept {
        return container[idx];
    }

    /**
     * @brief Index operator
     *
     * Square braces operator for vector
     *
     * @param idx index of element
     * @return const_reference to element by index
     */
    const_reference operator[] (size_type idx) const noexcept {
        return container[idx];
    }

    /**
     * @brief Get element at index
     *
     * Gets a reference to element by index with bounds check
     *
     * @param idx index of element
     * @return reference to element by index
     * @throws std::invalid_argument
     */
    reference at(size_type idx) {
        if (idx >= cur_n) {
            throw std::invalid_argument("Index is greater than size");
        }

        return (*this)[idx];
    }

    /**
     * @brief Get element at index
     *
     * Gets a reference to element by index with bounds check
     *
     * @param idx index of element
     * @return const_reference to element by index
     * @throws std::invalid_argument
     */
    const_reference at(size_type idx) const {
        if (idx >= cur_n) {
            throw std::invalid_argument("Index is greater than size");
        }

        return (*this)[idx];
    }

    /**
     * @brief begin iterator
     *
     * Begin() iterator for Vector class ( points to the beginning of vector )
     *
     * @return iterator to beginning
     */
    iterator begin() noexcept { return iterator(container); }

    /**
     * @brief end iterator
     *
     * End() iterator for Vector class ( points to the beginning of vector )
     *
     * @return iterator to end
     */
    iterator end() noexcept { return iterator(container + cur_n); }

    /**
     * @brief begin iterator
     *
     * Begin() iterator for Vector class ( points to the beginning of vector )
     *
     * @return const_iterator to beginning
     */
    const_iterator begin() const noexcept { return iterator(container); }

    /**
     * @brief end iterator
     *
     * End() iterator for Vector class ( points to the beginning of vector )
     *
     * @return const_iterator to end
     */
    const_iterator end() const noexcept { return iterator(container + cur_n); }

    /**
     * @brief сbegin iterator
     *
     * Сbegin() const iterator for Vector class ( points to the beginning of vector )
     *
     * @return const_iterator to beginning
     */
    const_iterator cbegin() const noexcept { return const_iterator(container); }

    /**
     * @brief сend iterator
     *
     * Сend() const iterator for Vector class ( points to the beginning of vector )
     *
     * @return const_iterator to end
     */
    const_iterator cend() const noexcept { return const_iterator(container + cur_n); }

    /**
     * @brief == operator
     *
     * Comparison operator for Vector class
     * Compares to reference to other instance
     *
     * @param o Vector reference
     * @return bool comparison result
     */
    bool operator==(const Vector &o) const noexcept {
        return cur_n == o.cur_n && std::equal(begin(), end(), o.begin(), o.end());
    }

    /**
     * @brief swap function
     *
     * Swap function for Vector class
     * Swaps fields with other instance
     *
     * @param o Vector reference
     */
    void swap(Vector &o) noexcept {
        std::swap(container, o.container);
        std::swap(cur_n, o.cur_n);
        std::swap(max_n, o.max_n);
    }

    /**
     * @brief size getter
     *
     * Getter of size field
     *
     * @return size of Vector
     */
    [[nodiscard]] size_type size() const noexcept { return cur_n; }

    /**
     * @brief max_size getter
     *
     * Getter of max_size that vector can fit
     *
     * @return max Vector size
     */
    [[nodiscard]] size_type max_size() const noexcept { return std::numeric_limits<size_type>::max(); }

    /**
     * @brief capacity getter
     *
     * Getter of capacity field
     *
     * @return capacity of Vector
     */
    [[nodiscard]] size_type capacity() const noexcept { return max_n; }

    /**
     * @brief is Vector empty
     *
     * Checks if this Vector instance is empty
     *
     * @return bool of whether Vector is empty or not
     */
    [[nodiscard]] bool empty() const noexcept { return cur_n == 0; }

    /**
     * @brief Generic emplace method
     *
     * Generic emplace method for Vector class
     * It uses variable list of arguments
     *
     * @tparam Args argument types
     * @param p constant iterator
     * @param args variable number of arguments
     * @return end() iterator to emplaced data
     */
    template <typename... Args>
    iterator emplace(const_iterator p, Args &&...args)
    requires std::constructible_from<T, Args...>
    {
        size_type dist = cend() - p;

        if (capacity() <= size()) {
            resize(capacity() + 1);
        }

        iterator i_end = end();
        //TODO: std::rotate
        while (i_end != end() - dist) {
            *i_end = std::move(*(i_end - 1));
            --i_end;
        }

        *i_end = value_type(std::forward<Args>(args)...);
        ++cur_n;

        return i_end + 1;
    }

    /**
     * @brief insert method for Vector
     *
     * Insert method from iterator and value
     *
     * @param p const_iterator to vector
     * @param t value to insert
     * @return iterator to end of inserted data
     */
    iterator insert(const_iterator p, const T &t) { return emplace(p, t); }

    /**
     * @brief insert method for Vector
     *
     * Insert method from iterator and rvalue
     *
     * @param p const_iterator where to insert
     * @param t rvalue to insert
     * @return 
     */
    iterator insert(const_iterator p, T &&t) { return emplace(p, std::move(t)); }

    /**
     * @brief insert() method for Vector
     *
     * Insert method for Vector from fill-value and number of elements
     *
     * @param p const_iterator
     * @param n how many elements to insert
     * @param t T value to fill
     * @return const_iterator to end of inserted data
     */
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

    /**
     * @brief insert() method
     *
     * insert() method for Vector from std::forward_iterator range
     *
     * @tparam I std::forward_iterator
     * @param p const_iterator
     * @param i_start beginning of the range
     * @param i_end end of the range
     * @return iterator end() of the inserted data
     */
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

    /**
     * @brief insert() method
     *
     * insert() method for Vector from initializer_list
     *
     * @param p const_iterator
     * @param il initializer_list
     * @return const_iterator
     */
    const_iterator insert(const_iterator p, std::initializer_list<T> il)
    requires std::move_constructible<T>
    {
        return insert(p, std::move_iterator(il.begin()), std::move_iterator(il.end()));
    }

    /**
     * @brief erase() method
     *
     * erase() method for Vector
     *
     * @param it iterator from where to erase
     * @return iterator to beginning of remaining data
     */
    iterator erase(const_iterator it) {
        if (empty()) {
            return end();
        }

        size_type distance = it - begin();
        for (auto i = begin() + distance; i != end() - 1; ++i) {
            *i = std::move(*(i + 1));
        }

        --cur_n;
        return begin() + distance;
    }

    /**
     * @brief erase() method
     *
     * erase() method for Vector in range
     *
     * @param it1 beginning of the range
     * @param it2 end of the range
     * @return iterator to beginning of remaining data
     */
    iterator erase(const_iterator it1, const_iterator it2) {
        iterator i_start1 = begin() + (it1 - cbegin());
        iterator i_start2 = begin() + (it2 - cbegin());

        while (i_start2 - i_start1 > 0) {
            i_start1 = erase(i_start1);
            --i_start2;
        }

        return i_start2;
    }

    /**
     * @brief assign() method
     *
     * assign() method for Vector from two iterators: start and end
     *
     * @tparam I std::forward_iterator
     * @param i1 beginning of the range
     * @param i2 end of the range
     */
    template<std::forward_iterator I>
    void assign(I i1, I i2) {
        if (!empty()) {
            erase(cbegin(), cend());
        }

        insert(cend(), i1, i2);
    }

    /**
     * @brief assign() method
     *
     * assign() method for Vector from initializer_list
     *
     * @param il std::initializer_list<T>
     */
    void assign(std::initializer_list<T> il) {
        if (!empty()) {
            erase(begin(), end());
        }

        insert(end(), std::move(il));
    }

    /**
     * @brief assign() method
     *
     * Assign method for Vector from number of elements and value
     *
     * @param n number of elements
     * @param t value to assign
     */
    void assign(size_type n, const T &t) {
        if (!empty()) {
            erase(begin(), end());
        }

        insert(end(), n, t);
    }

    /**
     * @brief push_back() method
     *
     * push_back() method for Vector from lvalue param
     *
     * @param t T type lvalue to insert
     */
    void push_back(const T &t) {
        insert(end(), t);
    }

    /**
     * @brief push_back() method
     *
     * push_back() method for Vector from rvalue param
     *
     * @param t T type rvalue to insert
     */
    void push_back(T &&t) {
        insert(end(), std::move(t));
    }

    /**
     * @brief Resize the container
     *
     * Resize() method for Vector to resize its container
     *
     * @param n new size
     */
    void resize(size_type n) {
        if (n == max_n) {
            return ;
        }

        long long to_copy = (n < size()) ? n : size();
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
