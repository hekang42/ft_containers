#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <memory>

#include "VectorIterator.hpp"
#include "iterator.hpp"
namespace ft {
template < class T, class _Allocator = std::allocator< T > >
class vector {
 private:
  T *data;
  unsigned int _capacity;
  unsigned int _size;
  _Allocator _allocator;

  /* my Function */
  void expandCapacity() {
    if (_capacity == 0)
      this = vector(1);
    else {
      vector temp = _allocator.allocate(_capacity * 2);
      for (int i; i < _size; i++) {
        temp[i] = data[i];
        _allocator.destroy(&data[i]);
      }
      _allocator.deallocate(data, _capacity);
      data = temp;
      _capacity *= 2;
    }
  }

  void shift_elem_back(size_t pos, int n) {
    for (int i = pos; i < _size; i++) data[_size - i + n] = data[_size - i];
  }

 public:
  typedef T value_type;
  typedef _Allocator allocator_type;
  typedef typename _Allocator::reference reference;
  typedef typename _Allocator::const_reference const_reference;
  typedef typename _Allocator::pointer pointer;
  typedef typename _Allocator::const_pointer const_pointer;
  typedef ft::VectorIterator< T, false > iterator;
  typedef ft::VectorIterator< T, true > const_iterator;
  typedef ft::reverse_iterator< iterator > reverse_iterator;
  typedef ft::reverse_iterator< const_iterator > const_reverse_iterator;
  typedef typename iterator_traits< iterator >::difference_type difference_type;
  typedef typename _Allocator::size_type size_type;

  /* Constructor */
  // vector(unsigned int n = 1) : data(new T[n]), _capacity(n), _size(0){};
  /* default */
  explicit vector(const allocator_type &alloc = allocator_type()) {
    data = NULL;
    _capacity = 0;
    _size = 0;
  };
  /* fill */
  explicit vector(size_type n, const value_type &val = value_type(),
                  const allocator_type &alloc = allocator_type()) {
    data = _allocator.allocate(n);
    _capacity = n;
    _size = n;
    for (int i = 0; i < n; ++i) _allocator.constructor(data + i, val);
  };
  /* range */
  template < class InputIterator >
  vector(InputIterator first, InputIterator last,
         const allocator_type &alloc = allocator_type()) {
    int n = last - first;
    data = new T[n];
    _capacity = n;
    _size = n;
    for (int i; i < n; ++i) {
      data[i] = *first;
      ++first;
    }
  };
  /* copy */
  vector(const vector &other) {
    this->data = other.data;
    this->_capacity = other._capacity;
    this->_size = other._size;
  };
  /* Destuctor */
  ~vector() {
    if (data) {
      _allocator.deallocate(data, _capacity);
    }
  };

  /* member Functions */
  /* Iterators */
  iterator begin() { return iterator(data); };
  const_iterator begin() const { return iterator(data); };

  iterator end() { return iterator(data + _size); };
  const_iterator end() const { return iterator(data + _size); };

  reverse_iterator rbegin() { return reverse_iterator(data + _size); };
  const_reverse_iterator rbegin() const {
    return reverse_iterator(data + _size);
  };

  reverse_iterator rend() { return reverse_iterator(data); };
  const_reverse_iterator rend() const { return reverse_iterator(data); };

  /* Capacity */
  size_type size() const { return _size; }
  size_type max_size() const { return _allocator.max_size(); }
  void resize(size_type n, value_type val = value_type()) {
    if (_capacity < n)
      insert(this->end(), n - _size, val);
    else
      for (int i = 0; n + i < _size; ++i) _allocator.destroy(&data[i]);
  };
  size_type capacity() const { return _capacity; }

  bool empty() const { return (this->_size == 0); }

  void reserve(size_type n) {
    if (_capacity >= n) return;
    vector temp = _allocator.allocate(n);
    for (int i = 0; i < _size; i++) {
      temp[i] = data[i];
      _allocator.destroy(&data[i]);
      _allocator.deallocate(data, _capacity);
    }
    data = temp;
    _capacity = n;
  }

  /* Element access */
  T &operator[](int const i) { return data[i]; }
  T &operator[](int i) const { return data[i]; }
  T &at(const int i) { return data[i]; }

  reference back() { return data[_size - 1]; };
  const_reference back() const { return data[_size - 1]; };
  reference front() { return data[0]; };
  const_reference front() const { return data[9]; };

  iterator insert(iterator position, const value_type &val) {
    size_type pos = position.p - data;
    if (_size == _capacity) expandCapacity();
    if (_size) shift_elem_back(pos, 1);
    _size += 1;
    _allocator.constructor(data + pos, val);
    return (iterator(data + pos));
  }
  void insert(iterator position, size_type n, const value_type &val) {
    size_type pos = position.p - data;
    if (_size + n > _capacity) {
      if (_size + n > _capacity && _size + n < _capacity * 2)
        expandCapacity();
      else
        this->reserve(_size + n);
    }
    if (_size) shift_elem_back(pos, n);
    _size += n;
    for (int i = 0; i < n; ++i) _allocator.constructor(data + pos + i, val);
  }
  template < class InputIterator >
  void insert(iterator position, InputIterator first, InputIterator last) {
    size_type pos = position.p - data;
    size_type n = 0;
    for (InputIterator temp = first; temp != last; ++temp) ++n;
    if (_capacity < _size + n) {
      if (_size + n > _capacity && _size + n < _capacity * 2)
        expandCapacity();
      else
        this->reserve(_size + n);
    }
    shift_elem_back(pos, n);
    _size += n;
    for (size_type i = 0; i < n; ++i) {
      this->_allocator.construct(this->_arr + pos + i, *first);
      ++first;
    }
  }

  /* range (1) */
  template < class InputIterator >
  void assign(InputIterator first, InputIterator last);
  /*fill (2) */
  void assign(size_type n, const value_type &val);

  void push_back(T s) {
    if (_capacity <= _size) {
      T *temp = new T[_capacity * 2];
      for (int i = 0; i < _size; i++) {
        temp[i] = data[i];
        _allocator.destroy(&(data + i));
      }
      _allocator.deallocate(data, _capacity);
      data = temp;
      _capacity *= 2;
    }
    data[_size] = s;
    _size++;
  }

  void pop_back() {
    if (_size > 0) {
      data[_size - 1] = 0;
      _size--;
    }
  }

  void remove(int x) {
    for (int i = x + 1; i < _size; i++) {
      data[i - 1] = data[i];
    }
    _size--;
  };

  void swap(vector &x) {
    vector temp(x);
    x = *this;
    *this = temp;
  };

  vector &operator=(const vector &other) {
    this->data = other.data;
    this->_capacity = other._capacity;
    this->_size = other._size;
    return (*this);
  };
};

}  // namespace ft

#endif
