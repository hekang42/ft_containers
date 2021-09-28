#ifndef VECTOR_HPP
#define VECTOR_HPP
#include "iterator.hpp"
#include <iterator>
namespace ft {
template < class T, class _Allocator = std::allocator< T > >
class vector {
 private:
  T *data;
  unsigned int _capacity;
  unsigned int _length;
  _Allocator _allocator;

 public:
  typedef T value_type;
  typedef _Allocator allocator_type;
  typedef typename _Allocator::reference reference;
  typedef typename _Allocator::const_reference const_reference;
  typedef typename _Allocator::pointer pointer;
  typedef typename _Allocator::const_pointer const_pointer;
  typedef 
  typedef typename iterator_traits<iterator>::deference_type difference_type;
  typedef typename _Allocator::size_type size_type;

  /* Constructor */
  // vector(unsigned int n = 1) : data(new T[n]), _capacity(n), _length(0){};
  /* default */
  explicit vector(const allocator_type &alloc = allocator_type()) {
    data = new T[1];
    _capacity = 1;
    _length = 0;
  };
  /* fill */
  explicit vector(size_type n, const value_type &val = value_type(),
                  const allocator_type &alloc = allocator_type()) {
    data = new T[n];
    _capacity = n;
    _length = n;
    for (int i = 0; i < n; ++i) data[i] = val;
  };
  /* range */
  template < class InputIterator >
  vector(InputIterator first, InputIterator last,
         const allocator_type &alloc = allocator_type()) {
    int n = last - first;
    data = new T[n];
    _capacity = n;
    _length = n;
    for (int i; i < n; ++i) {
      data[i] = *first;
      ++first;
    }
  };
  /* copy */
  vector(const vector &other) {
    this->data = other.data;
    this->_capacity = other._capacity;
    this->_length = other._length;
  };
  /* Destuctor */
  ~vector() {
    if (data) {
      delete[] data;
    }
  };


  /* member Functions */
  /* range (1) */
  template <class InputIterator>
    void assign (InputIterator first, InputIterator last);
  /*fill (2) */
  void assign (size_type n, const value_type& val);



  void push_back(T s) {
    if (_capacity <= _length) {
      T *temp = new T[_capacity * 2];
      for (int i = 0; i < _length; i++) temp[i] = data[i];
      delete[] data;
      data = temp;
      _capacity *= 2;
    }
    data[_length] = s;
    _length++;
  }

  void pop_back() {
    if (_length > 0) {
      data[_length - 1] = 0;
      _length--;
    }
  }

  reference back()
  {
    return data[_length - 1];
  };
  const_reference back() const
  {
    return data[_length - 1];
  };



  T &operator[](int const i) { return data[i]; }
  T &operator[](int i) const { return data[i]; }
  T &at(const int i) { return data[i]; }

  void remove(int x) {
    for (int i = x + 1; i < _length; i++) {
      data[i - 1] = data[i];
    }
    _length--;
  };

  void swap(vector &x) {
    vector temp(x);
    x = *this;
    *this = temp;
  };

  vector &operator=(const vector &other) {
    this->data = other.data;
    this->_capacity = other._capacity;
    this->_length = other._length;
    return (*this);
  };

  bool empty() const { return (this->_length == 0); }
  size_type size() const { return _length; }
  size_type capacity() const { return _capacity; }
};

}  // namespace ft

#endif
