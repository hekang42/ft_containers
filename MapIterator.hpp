#if !defined(MAPITERATOR_HPP)
#define MAPITERATOR_HPP

#include "iterator.hpp"
#include "utils.hpp"
namespace ft {
//bidirectional iterator
template < typename T, class Compare, bool IsConst >
class MapIterator {
 public:
  typedef T value_type;
  typedef std::ptrdiff_t difference_type;
  typedef typename choose< IsConst, const T *, T * >::type pointer;
  typedef typename choose< IsConst, const T &, T & >::type reference;
  typedef ft::bidirectional_iterator_tag iterator_category;

  pointer p;

  MapIterator(T *x = NULL) : p(x){};
  MapIterator(const MapIterator< T, false > &other) : p(other.p){};
  ~MapIterator(){};

  MapIterator &operator=(const MapIterator &other) {
    if (this != &other) this->p = other.p;
    return *this;
  };

  pointer operator->() const { return (p); }
  MapIterator &operator++() {
    ++p;
    return *this;
  }
  MapIterator operator++(int) {
    MapIterator tmp(*this);
    operator++();
    return tmp;
  }
  MapIterator &operator--() {
    --p;
    return *this;
  }
  MapIterator operator--(int) {
    MapIterator tmp(*this);
    operator--();
    return tmp;
  }

  bool operator==(const MapIterator< T, true > &rhs) const {
    return p == rhs.p;
  }
  bool operator==(const MapIterator< T, false > &rhs) const {
    return p == rhs.p;
  }
  bool operator!=(const MapIterator< T, true > &rhs) const {
    return p != rhs.p;
  }
  bool operator!=(const MapIterator< T, false > &rhs) const {
    return p != rhs.p;
  }
  reference operator*() { return *p; }
};
}  // namespace ft

#endif  // MAPITERATOR_HPP