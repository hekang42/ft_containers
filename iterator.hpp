#ifndef ITERATOR
#define ITERATOR
// #include <iterator>
namespace ft {

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : input_iterator_tag, output_iterator_tag {};
struct bidirectional_iterator_tag : forward_iterator_tag {};
struct random_access_iterator_tag : bidirectional_iterator_tag {};

template < class Iterator >
class iterator_traits {
 public:
  typedef typename Iterator::iterator_category iterator_category;
  typedef typename Iterator::difference_type difference_type;
  typedef typename Iterator::value_type value_type;
  typedef typename Iterator::pointer pointer;
  typedef typename Iterator::reference reference;
};
template < class T >
class iterator_traits< T* > {
 public:
  typedef ptrdiff_t difference_type;
  typedef T value_type;
  typedef T* pointer;
  typedef T& reference;
  typedef random_access_iterator_tag iterator_category;
};
template < class T >
class iterator_traits< const T* > {
 public:
  typedef ptrdiff_t difference_type;
  typedef T value_type;
  typedef const T* pointer;
  typedef const T& reference;
  typedef random_access_iterator_tag iterator_category;
};

template < class Iterator >
class reverse_iterator {
 protected:
 public:
  Iterator current;
  typedef Iterator iterator_type;
  typedef
      typename iterator_traits< Iterator >::iterator_category iterator_category;
  typedef typename iterator_traits< Iterator >::value_type value_type;
  typedef typename iterator_traits< Iterator >::difference_type difference_type;
  typedef typename iterator_traits< Iterator >::pointer pointer;
  typedef typename iterator_traits< Iterator >::reference reference;

  /**
   * @brief aqsdasdas
   */
  reverse_iterator() : current(){};
  /**
   * @brief aqsdasdas
   * @param it asdasdss
   */
  explicit reverse_iterator(iterator_type it) : current(it){};
  template < class Iter >
  reverse_iterator(const reverse_iterator< Iter >& rev_it)
      : current(rev_it.base()){};
  iterator_type base() const { return current; };

  reference operator*() const {
    iterator_type iter = current;
    return *--iter;
  };
  pointer operator->() const { return &(operator*()); };
  reverse_iterator& operator++() {
    --current;
    return *this;
  };
  reverse_iterator operator++(int) {
    reverse_iterator __tmp(*this);
    --current;
    return __tmp;
  };
  reverse_iterator& operator--() {
    ++current;
    return *this;
  };
  reverse_iterator operator--(int) {
    reverse_iterator __tmp(*this);
    ++current;
    return __tmp;
  };
  reverse_iterator operator+(difference_type __n) const {
    return reverse_iterator(current - __n);
  }
  reverse_iterator& operator+=(difference_type __n) {
    current -= __n;
    return *this;
  }
  reverse_iterator operator-(difference_type __n) const {
    return reverse_iterator(current + __n);
  }
  reverse_iterator& operator-=(difference_type __n) {
    current += __n;
    return *this;
  }
  reference operator[](difference_type __n) const { return *(*this + __n); }
};
template < class _Iter1, class _Iter2 >
bool operator==(const reverse_iterator< _Iter1 >& __x,
                const reverse_iterator< _Iter2 >& __y) {
  return __x.base() == __y.base();
}
template < class _Iter1, class _Iter2 >
bool operator<(const reverse_iterator< _Iter1 >& __x,
               const reverse_iterator< _Iter2 >& __y) {
  return __x.base() > __y.base();
}

template < class _Iter1, class _Iter2 >
bool operator!=(const reverse_iterator< _Iter1 >& __x,
                const reverse_iterator< _Iter2 >& __y) {
  return __x.base() != __y.base();
}

template < class _Iter1, class _Iter2 >
bool operator>(const reverse_iterator< _Iter1 >& __x,
               const reverse_iterator< _Iter2 >& __y) {
  return __x.base() < __y.base();
}

template < class _Iter1, class _Iter2 >
bool operator>=(const reverse_iterator< _Iter1 >& __x,
                const reverse_iterator< _Iter2 >& __y) {
  return __x.base() <= __y.base();
}

template < class _Iter1, class _Iter2 >
bool operator<=(const reverse_iterator< _Iter1 >& __x,
                const reverse_iterator< _Iter2 >& __y) {
  return __x.base() >= __y.base();
}

template < class Iterator >
typename reverse_iterator< Iterator >::difference_type operator-(
    const reverse_iterator< Iterator >& __x,
    const reverse_iterator< Iterator >& __y) {
  return __y.base() - __x.base();
}

template < class _Iter >
reverse_iterator< _Iter > operator+(
    typename reverse_iterator< _Iter >::difference_type __n,
    const reverse_iterator< _Iter >& __x) {
  return reverse_iterator< _Iter >(__x.base() - __n);
}

}  // namespace ft
#endif