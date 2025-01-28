#pragma once
#include <memory> // For std::allocator
#include <algorithm> // For std::uninitialized_copy, std::max
#include <cstddef>   // For ptrdiff_t

template <class T> class Vec {
public:

    typedef T* iterator;
    typedef const T* const_iterator;
    typedef size_t size_type;
    typedef T value_type;

    Vec() { create(); }
    explicit Vec(size_type n, const T& t = T()) { create(n, t); }
    Vec(const Vec& v) { create(v.begin(), v.end()); }

    Vec& operator=(const Vec&); // as defined in §11.3.2/196
    ~Vec() { uncreate(); }

    T& operator[](size_type i) { return data[i]; }
    const T& operator[](size_type i) const { return data[i]; }

    void push_back(const T& t) {
        if (avail == limit)
            grow();
        unchecked_append(t);
        std::cout << limit - data << "  allocated size after pushing back" << std::endl;

    }
    ///
    void push_at(size_type index,const T& t) {
        if (avail == limit)
            grow();
        unchecked_append_at(index,t);
    }
    ///
    ///
    void pop_back(bool autoshrink = true) {
        if (avail == data) return;
        unchecked_delete();
        // if size == 100 ~
        if(autoshrink)
        if ((avail - data - 1) * 2 <= (limit - data - 1) )
            shrink();
        std::cout << limit - data << "  allocated size after popping back" << std::endl;
    }
    ///
    ///
    void pop_at(size_type index) {
        if (avail == data) return;
        unchecked_delete_at(index);
        if ((avail - data - 1) * 2 <= (limit - data - 1))
            shrink();
        std::cout << limit - data << "  allocated size after popping index: "<< index << std::endl;
    }
    ///
    /// ~ does not work with reserve 
    void clear() {
        while (size() > 0)
            pop_back(false);
        // shrink only once after finished
        shrink();
    }
    ///
    ///
    void reserve(size_type inreservesize)
    {
        if (inreservesize < size()) return;
        else
        {
            // when growing, allocate twice as much space as currently in use
            reservesize = inreservesize;
            // allocate new space and copy existing elements to the new space
            iterator new_data = alloc.allocate(reservesize);
            iterator new_avail = std::uninitialized_copy(data, avail, new_data);

            // return the old space
            uncreate();

            // reset pointers to point to the newly allocated space
            data = new_data;
            avail = new_avail;
            limit = data + reservesize;
        }
    }
    ///
    size_type size() const { return avail - data; }

    iterator begin() { return data; }
    const_iterator begin() const { return data; }

    iterator end() { return avail; }
    const_iterator end() const { return avail; }

private:
    iterator data; // first element in the Vec
    iterator avail; // (one past) the last element in the Vec
    iterator limit; // (one past) the allocated memory

    typedef std::allocator<T> allocator_type;
    // facilities for memory allocation
    allocator_type alloc; // object to handle memory allocation
    ///
    static T vecmax(const T& left, const T& right) {
        return left > right ? left : right;
    }
    ///
    ///
    size_type reservesize = -1;
    ///
    // allocate and initialize the underlying array
    void create();
    void create(size_type, const T&);
    void create(const_iterator, const_iterator);

    // destroy the elements in the array and free the memory
    void uncreate();

    // support functions for push/pop
    void grow();
    ///
    void shrink();
    ///
    void unchecked_append(const T&);
    ///
    void unchecked_append_at(size_type index,const T&);
    ///
    void unchecked_delete();
    ///
    void unchecked_delete_at(size_type index);
    ///
};



template <class T> void Vec<T>::create()
{
    data = avail = limit = 0;
}

template <class T> void Vec<T>::create(size_type n, const T& val)
{
    data = alloc.allocate(n);
    limit = avail = data + n;
    uninitialized_fill(data, limit, val);
}

template <class T>
void Vec<T>::create(const_iterator i, const_iterator j)
{
    data = alloc.allocate(j - i);
    limit = avail = uninitialized_copy(i, j, data);
}

template <class T> void Vec<T>::uncreate()
{
    if (data) {
        // destroy (in reverse order) the elements that were constructed
        iterator it = avail;
        while (it != data)
            alloc.destroy(--it);

        // return all the space that was allocated
        alloc.deallocate(data, limit - data);
    }

    // reset pointers to indicate that the Vec is empty again
    data = limit = avail = 0;
}

template <class T> void Vec<T>::grow()
{
    // when growing, allocate twice as much space as currently in use
    size_type new_size = vecmax(2 * (limit - data), ptrdiff_t(1));
    std::cout  << "upsized to :" << new_size << std::endl;
    // allocate new space and copy existing elements to the new space
    iterator new_data = alloc.allocate(new_size);
    iterator new_avail = std::uninitialized_copy(data, avail, new_data);

    // return the old space
    uncreate();

    // reset pointers to point to the newly allocated space
    data = new_data;
    avail = new_avail;
    limit = data + new_size;
}

template<class T>
inline void Vec<T>::shrink()
{
    size_type new_size;
    // for when Vec is reserved
    if (reservesize != -1)
    {
        // new size can't be smaller than reserved size
        new_size = vecmax((data == avail ? 0 : (limit - avail)), reservesize);
        ///already at reserve size and can't go lowr , so it shouldn't run for no reason 
        if (limit - data == reservesize) return;
    }
    else
    { 
     new_size = (data == avail ? 0 : (limit - avail));
    }
    std::cout << "downsized to :" << new_size << std::endl;
    // allocate new space and copy existing elements to the new space
    iterator new_data = alloc.allocate(new_size);
    iterator new_avail = std::uninitialized_copy(data, avail, new_data);
    // return the old space
    uncreate();
    // reset pointers to point to the newly allocated space
    data = new_data;
    avail = new_avail;
    limit = data + new_size;
}

template <class T> void Vec<T>::unchecked_append(const T& val)
{
    alloc.construct(avail++, val);
}

template<class T>
inline void Vec<T>::unchecked_append_at(size_type index, const T& val)
{
    // shift everything towards the end (>> ?) 
    for (auto it = end(); it > begin() + index ; it--)
    {
        *it = *(it - 1);
    }   
    alloc.construct(begin() + index, val);
    // one more element therefore avail is ++
    avail++;
}

template<class T>
inline void Vec<T>::unchecked_delete()
{
    // avail is shifted left so it points to the last element now , and that space is freed up 
    alloc.destroy(--avail);
}

template<class T>
inline void Vec<T>::unchecked_delete_at(size_type index)
{
    // free up the location
    alloc.destroy(begin() + index);
    // shift stuff to left 
    for (auto it = begin() + index; it < end() ; it++)
    {
        *it = *(it + 1);
    }
    // one less element therefore avail is --
    avail--;
}

