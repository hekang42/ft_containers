#if !defined(VECTORITERATOR_HPP)
#define VECTORITERATOR_HPP

#include "iterator.hpp"
#include "utils.hpp"
namespace ft {

template < typename T, bool IsConst >
class VectorIterator {
 public:
  typedef T value_type;
  typedef std::ptrdiff_t difference_type;
  typedef typename choose< IsConst, const T *, T * >::type pointer;
  typedef typename choose< IsConst, const T &, T & >::type reference;
  typedef ft::random_access_iterator_tag iterator_category;

  pointer p;
  VectorIterator(T *x = NULL) : p(x){};
  VectorIterator(const VectorIterator< T, false > &other) : p(other.p){};
  ~VectorIterator(){};

  VectorIterator &operator=(const VectorIterator &other) {
    if (this != &other) this->p = other.p;
    return *this;
  };
  pointer operator->() const { return (p); }
  VectorIterator &operator++() {
    ++p;
    return *this;
  }
  VectorIterator operator++(int) {
    VectorIterator tmp(*this);
    operator++();
    return tmp;
  }
  VectorIterator &operator--() {
    --p;
    return *this;
  }
  VectorIterator operator--(int) {
    VectorIterator tmp(*this);
    operator--();
    return tmp;
  }

  // Random Access
  VectorIterator operator+(int n) const { return (VectorIterator(p + n)); }
  VectorIterator operator-(int n) const { return (VectorIterator(p - n)); }
  difference_type operator-(const VectorIterator< T, true > &iter) const {
    return (p - iter.p);
  }
  difference_type operator-(const VectorIterator< T, false > &iter) const {
    return (p - iter.p);
  }
  VectorIterator operator+=(int n) const {
    this->p += n;
    return *this;
  }
  VectorIterator operator-=(int n) const {
    this->p -= n;
    return *this;
  }
  bool operator==(const VectorIterator< T, true > &rhs) const {
    return p == rhs.p;
  }
  bool operator==(const VectorIterator< T, false > &rhs) const {
    return p == rhs.p;
  }
  bool operator!=(const VectorIterator< T, true > &rhs) const {
    return p != rhs.p;
  }
  bool operator!=(const VectorIterator< T, false > &rhs) const {
    return p != rhs.p;
  }
  bool operator>(const VectorIterator< T, true > &rhs) const {
    return p > rhs.p;
  }
  bool operator>(const VectorIterator< T, false > &rhs) const {
    return p > rhs.p;
  }
  bool operator>=(const VectorIterator< T, true > &rhs) const {
    return p >= rhs.p;
  }
  bool operator>=(const VectorIterator< T, false > &rhs) const {
    return p >= rhs.p;
  }
  bool operator<(const VectorIterator< T, true > &rhs) const {
    return p < rhs.p;
  }
  bool operator<(const VectorIterator< T, false > &rhs) const {
    return p < rhs.p;
  }
  bool operator<=(const VectorIterator< T, true > &rhs) const {
    return p < rhs.p;
  }
  bool operator<=(const VectorIterator< T, false > &rhs) const {
    return p < rhs.p;
  }
  reference operator*() { return *p; }
};
template < typename T, bool IsConst >
VectorIterator< T, IsConst > operator+(
    typename VectorIterator< T, IsConst >::difference_type n,
    const VectorIterator< T, IsConst > &iter) {
  return (VectorIterator< T, IsConst >(iter + n));
}
}  // namespace ft
#endif  // VECTORITERATOR_HPP