#if !defined(MAPITERATOR_HPP)
#define MAPITERATOR_HPP

#include "iterator.hpp"
#include "utils.hpp"
#include "BTree.hpp"
namespace ft {

template < typename T >
struct TreeNode;
// bidirectional iterator
template < typename T, class Compare, bool IsConst >
class MapIterator {
 private:
  typedef ft::TreeNode< T > node;
  typedef ft::TreeNode< T > *node_pointer;

 public:
  typedef T value_type;
  typedef std::ptrdiff_t difference_type;
  typedef typename choose< IsConst, const T *, T * >::type pointer;
  typedef typename choose< IsConst, const T &, T & >::type reference;
  typedef ft::bidirectional_iterator_tag iterator_category;

 private:
  node_pointer _node;
  node_pointer	minValueNode(node_pointer node)
    {
      if (node == nullptr)
        return (node);
      while (node->_left != nullptr)
        node = node->_left;
      return (node);
    }
    node_pointer	maxValueNode(node_pointer node)
    {
      if (node == nullptr)
        return (node);
      while (node->_right != nullptr)
        node = node->_right;
      return (node);
	}
 public:
  MapIterator() : _node(nullptr) {}
  MapIterator(T *x = NULL) : _node(x) {}
  MapIterator(node_pointer node) : _node(node) {}
  MapIterator(const MapIterator &other) : _node(other._node) {}
  virtual ~MapIterator(){};
  MapIterator &operator=(const MapIterator &other) {
    if (this != &other) this->_node = other._node;
    return *this;
  };

  node_pointer base() const { return (this->_node); }

  pointer operator->() const { return (&(_node->_value)); }

  MapIterator &operator++() {
    if (_node->_right != nullptr) {
      _node = minValueNode(_node->right);
      return (*this);
    }
    while (_node->_parent && _node->_parent->_left != _node)
      _node = _node->_parent;
    if (_node->parent) _node = _node->_parent;
    return *this;
  }
  MapIterator operator++(int) {
    MapIterator tmp = *this;
    ++(*this);
    return tmp;
  }
  MapIterator &operator--() {
    if (_node->_left != nullptr) {
      _node = maxValueNode(_node->_left);
      return (*this);
    }
    while (_node->_parent && _node->_parent->_right != _node)
      _node = _node->_parent;
    if (_node->_parent)
      _node = _node->_parent;
    else
      _node = nullptr;
    return *this;
  }
  MapIterator operator--(int) {
    MapIterator tmp = *this;
    --(*this);
    return tmp;
  }

  bool operator==(const MapIterator< T, Compare, true > &rhs) const {
    return _node == rhs._node;
  }
  bool operator==(const MapIterator< T, Compare, false > &rhs) const {
    return _node == rhs._node;
  }
  bool operator!=(const MapIterator< T, Compare, true > &rhs) const {
    return _node != rhs._node;
  }
  bool operator!=(const MapIterator< T, Compare, false > &rhs) const {
    return _node != rhs._node;
  }
};
}  // namespace ft

#endif  // MAPITERATOR_HPP