#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <iostream>
namespace ft {
template < class _Tp, class _Allocator = std::allocator< _Tp > >
class vector {
private:
    typedef _Allocator allocator_type;
    typedef typename __alloc_traits::size_type size_type;

public:
    typedef _Tp value_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;

    vector() { _data = allocator_type().constructor(0); };
    vector(int n, T data) {

    };
    vector(vector& other) {

    };
    vector(iterator& first, iterator& last) {

    };
};
} // namespace ft
#endif
