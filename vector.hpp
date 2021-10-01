#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <memory>

#include "VectorIterator.hpp"
#include "iterator.hpp"
namespace ft
{
  template <class T, class _Allocator = std::allocator<T> >
  class vector
  {
  private:
    /* my Function */
    void expandCapacity()
    {
      if (_capacity == 0)
        {
          _capacity = 1;
          data = _allocator.allocate(1);
          _size= 0;
        }
      else
      {
        pointer temp = _allocator.allocate(_capacity * 2);
        for (size_type i=0; i < _size; i++)
        {
          temp[i] = data[i];
          _allocator.destroy(&data[i]);
        }
        _allocator.deallocate(data, _capacity);
        data = temp;
        _capacity *= 2;
      }
    }

    void shift_elem_back(typename _Allocator::size_type pos, int n)
    {
      for (size_type i = pos; i < _size; i++)
        data[_size - i + n] = data[_size - i];
    }
    void shift_elem_front(typename _Allocator::size_type pos, int n)
    {
      for (size_type i = pos; i < _size; i++)
        data[pos + i] = data[pos + i + n];
    }

  public:
    typedef T value_type;
    typedef _Allocator allocator_type;
    typedef typename _Allocator::reference reference;
    typedef typename _Allocator::const_reference const_reference;
    typedef typename _Allocator::pointer pointer;
    typedef typename _Allocator::const_pointer const_pointer;
    typedef ft::VectorIterator<T, false> iterator;
    typedef ft::VectorIterator<T, true> const_iterator;
    typedef ft::reverse_iterator<iterator> reverse_iterator;
    typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
    typedef typename iterator_traits<iterator>::difference_type difference_type;
    typedef typename _Allocator::size_type size_type;

  private:
    pointer data;
    unsigned int _capacity;
    unsigned int _size;
    _Allocator _allocator;

  public:
    /* Construct */
    // vector(unsigned int n = 1) : data(new T[n]), _capacity(n), _size(0){};
    /* default */
    explicit vector(const allocator_type &alloc = allocator_type())
    {
      data = NULL;
      _capacity = 0;
      _size = 0;
      _allocator = alloc;
    };
    /* fill */
    explicit vector(size_type n, const value_type &val = value_type(),
                    const allocator_type &alloc = allocator_type()) : data(NULL), _capacity(n), _size(n), _allocator(alloc)
    {
      data = _allocator.allocate(n);
      for (size_type i = 0; i < n; ++i)
        _allocator.construct(data + i, val);
    };
    /* range */
    template <class InputIterator>
    vector(InputIterator first, InputIterator last,
           const allocator_type &alloc = allocator_type(), typename ft::enable_if< !ft::is_integral<InputIterator>::value >::type* = NULL) : data(NULL), _allocator(alloc)
    {
      int n = 0;
      for (InputIterator i = first; i != last; ++i)
        n++;
      data = _allocator.allocate(n);
      _capacity = n;
      _size = n;
      for (int i = 0; i < n; ++i)
      {
        _allocator.construct(data + i, *first);
        first++;
      }
    };
    /* copy */
    vector(const vector &other)
    {
      data = NULL;
      _allocator = other.get_allocator();
      _size = 0;
      _capacity = 0;
      reserve(other._size);
      insert(data, other.begin(), other.end());

    };
    /* Destuctor */
    ~vector()
    {
      if (data)
      {
        clear();
        _allocator.deallocate(data, _capacity);
      }
    };

    /* member Functions */
    /* Iterators */
    iterator begin() { return iterator(data); };
    const_iterator begin() const { return data; };

    iterator end() { return iterator(data + _size); };
    const_iterator end() const { return iterator(data + _size); };

    reverse_iterator rbegin() { return reverse_iterator(data + _size); };
    const_reverse_iterator rbegin() const
    {
      return reverse_iterator(data + _size);
    };

    reverse_iterator rend() { return reverse_iterator(data); };
    const_reverse_iterator rend() const { return reverse_iterator(data); };

    /* Capacity */
    size_type size() const { return _size; }
    size_type max_size() const { return _allocator.max_size(); }
    void resize(size_type n, value_type val = value_type())
    {
      if (_capacity < n)
        insert(this->end(), n - _size, val);
      else
        for (int i = 0; n + i < _size; ++i)
          _allocator.destroy(&data[i]);
    };
    size_type capacity() const { return _capacity; }

    bool empty() const { return (this->_size == 0); }

    void reserve(size_type n)
    {
      if (_capacity >= n)
        return;
      pointer temp = _allocator.allocate(n);
      for (size_type i = 0; i < _size; i++)
      {
        _allocator.construct(temp+i, *(data+i));
        _allocator.destroy(data + i);
      }
      _allocator.deallocate(data, _capacity);
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

    /* Modifiers */
    /* range (1) */
    template <class InputIterator>
    void assign(InputIterator first, InputIterator last)
    {
      this->clear();
      this->insert(data, first, last);
    }
    /*fill (2) */
    void assign(size_type n, const value_type &val)
    {
      this->clear();
      this->insert(data, n, val);
    }

    void push_back(T s)
    {
      if (_capacity <= _size)
        expandCapacity();
      _allocator.construct(data + _size, s);
      _size++;
    }

    void pop_back()
    {
      if (_size > 0)
        _allocator.destroy(data + --_size);
    }

    iterator insert(iterator position, const value_type &val)
    {
      size_type pos = position.p - data;
      if (_size == _capacity)
        expandCapacity();
      if (_size)
        shift_elem_back(pos, 1);
      _size += 1;
      _allocator.construct(data + pos, val);
      return (iterator(data + pos));
    }
    void insert(iterator position, size_type n, const value_type &val)
    {
      size_type pos = position.p - data;
      if (_size + n > _capacity)
      {
        if (_size + n > _capacity && _size + n < _capacity * 2)
          expandCapacity();
        else
          this->reserve(_size + n);
      }
      if (_size)
        shift_elem_back(pos, n);
      _size += n;
      for (size_type i = 0; i < n; ++i)
        _allocator.construct(data + pos + i, val);
    }
    template <class InputIterator>
    void insert(iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = NULL)
    {
      size_type pos = position.p - data;
      size_type n = 0;
      for (InputIterator temp = first; temp != last; ++temp)
        ++n;
      if (_capacity < _size + n)
      {
        if (_size + n > _capacity && _size + n < _capacity * 2)
          expandCapacity();
        else
          this->reserve(_size + n);
      }
      shift_elem_back(pos, n);
      _size += n;
      for (size_type i = 0; i < n; ++i)
      {
        this->_allocator.construct(data + pos + i, *first);
        ++first;
      }
    }

    iterator erase(iterator position)
    {
      size_type pos = position.p - data;
      _allocator.destroy(data + pos);
      shift_elem_front(pos, 1);
      _size -= 1;
      return (position);
    }
    iterator erase(iterator first, iterator last)
    {
      size_type pos = first.p - data;
      size_type n = last.p - first.p;
      for (iterator i = first; i != last; ++i)
      {
        _allocator.destroy(data + pos);
        ++pos;
      }
      shift_elem_front(pos, n);
      _size -= n;
      return (first);
    }

    void clear()
    {
      for (size_type i = 0; i < _size; ++i)
        _allocator.destroy(data + i);
      _size = 0;
    }
    /* Allocator */
    allocator_type get_allocator() const { return (_allocator); }

    /* Non-member function overloads */
    void swap(vector &x)
    {
      this->data = x.data;
      this->_size = x._size;
      this->_capacity = x._capacity;
    };

    // void remove(int x) {
    //   for (int i = x + 1; i < _size; i++) {
    //     data[i - 1] = data[i];
    //   }
    //   _size--;
    // };

    vector &operator=(const vector &other)
    {
      if (this != &other){
					this->reserve(other._size);
					assign(other.begin(), other.end());
      }
      return (*this);
    };
  };

  template <class T, class Alloc>
  void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
  {
    x.swap(y);
  }


  template <class T, class Alloc>
  bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
  {
    if (lhs.size() != rhs.size())
      return false;
    return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
  }
  template <class T, class Alloc>
  bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
  {
    return (!(lhs == rhs));
  }
  template <class T, class Alloc>
  bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
  {
    return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
  }
  template <class T, class Alloc>
  bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
  {
    return (!(rhs < lhs));
  }
  template <class T, class Alloc>
  bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
  {
    return (rhs < lhs);
  }
  template <class T, class Alloc>
  bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
  {
    return (!(lhs < rhs));
  }
} // namespace ft

#endif
