#if !defined(VECTORITERATOR_HPP)
#define VECTORITERATOR_HPP
#include "utils.hpp"
#include <iterator>
namespace ft {

template < typename T, bool IsConst >
class VectorIterator {
 private:
  int* p;

 public:
	typedef T         value_type;
    typedef std::ptrdiff_t  difference_type;
    typedef T*   pointer;
    typedef T& reference;
    typedef iterator::random_access_iterator_tag  iterator_category;


  VectorIterator(int* x) : p(x){};
  VectorIterator(const VectorIterator& other) : p(other.p){};
  ~VectorIterator();

  VectorIterator operator->() const { return (&(*this->_ptr)); }
  VectorIterator& operator++() {
    ++p;
    return *this;
  }
  VectorIterator operator++(int) {
    VectorIterator tmp(*this);
    operator++();
    return tmp;
  }
  VectorIterator& operator--() {
    --p;
    return *this;
  }
  VectorIterator operator--(int) {
    VectorIterator tmp(*this);
    operator--();
    return tmp;
  }
  VectorIterator& operator=(const VectorIterator& other) {
    this = other.p;
    return *this;
  };

  bool operator==(const VectorIterator& rhs) const { return p == rhs.p; }
  bool operator!=(const VectorIterator& rhs) const { return p != rhs.p; }
  bool operator>(const VectorIterator& rhs) const { return p > rhs.p; }
  bool operator>=(const VectorIterator& rhs) const { return p >= rhs.p; }
  bool operator<(const VectorIterator& rhs) const { return p < rhs.p; }
  bool operator<=(const VectorIterator& rhs) const { return p <= rhs.p; }
  int& operator*() { return *p; }
};
}  // namespace ft
#endif  // VECTORITERATOR_HPP