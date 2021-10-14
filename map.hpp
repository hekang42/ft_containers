#ifndef MAP_HPP
#define MAP_HPP
#include <memory>

#include "BTree.hpp"
#include "MapIterator.hpp"
#include "iterator.hpp"
#include "utils.hpp"
namespace ft {
template < class Key, class T, class Compare = less< Key >,
           class Alloc = std::allocator< ft::pair< const Key, T > > >
class map {
 public:
  typedef Key key_type;
  typedef T mapped_type;
  typedef pair< const key_type, mapped_type > value_type;
  typedef Compare key_compare;
  typedef ptrdiff_t difference_type;

  // reference
  class value_compare : binary_function< value_type, value_type, bool > {
    friend class map;

   protected:
    Compare comp;
    value_compare(Compare c)
        : comp(c) {}  // constructed with map's comparison object
   public:
    typedef bool result_type;
    typedef value_type first_argument_type;
    typedef value_type second_argument_type;
    bool operator()(const value_type& x, const value_type& y) const {
      return comp(x.first, y.first);
    }
  };

  typedef Alloc allocator_type;
  typedef typename allocator_type::reference reference;
  typedef typename allocator_type::const_reference const_reference;
  typedef typename allocator_type::pointer pointer;
  typedef typename allocator_type::const_pointer const_pointer;
  typedef typename ft::MapIterator< value_type, value_compare, false > iterator;
  typedef typename ft::MapIterator< value_type, value_compare, true >
      const_iterator;
  typedef ft::reverse_iterator< iterator > reverse_iterator;
  typedef ft::reverse_iterator< const_iterator > const_reverse_iterator;
  typedef typename allocator_type::size_type size_type;

 private:
  key_compare _comp;
  allocator_type _alloc;
  BinaryTree< value_type, value_compare, allocator_type > _btree;

 public:
  /* Construct Map */
  /* empty (1) */
  explicit map(const key_compare& comp = key_compare(),
               const allocator_type& alloc = allocator_type())
      : _comp(comp), _alloc(alloc), _btree(value_compare(comp), alloc) {}

  /* range (2) */
  template < class InputIterator >
  map(InputIterator first, InputIterator last,
      const key_compare& comp = key_compare(),
      const allocator_type& alloc = allocator_type())
      : _comp(comp), _alloc(alloc), _btree(value_compare(comp), alloc) {
    this->insert(first, last);
  };
  /* copy (3) */
  map(const map& x) : _comp(x._comp), _alloc(x._alloc), _btree(x.btree){};

  map& operator=(const map& other) {
    if (this != other) {
      (this->_btree) = (other._btree);
    }
    return (*this);
  }
  ~map(){};

  /* member function */
  /* Iterator */
  iterator begin() { return _btree.begin(); }
  const_iterator begin() const { return _btree.begin(); };
  iterator end() { return _btree.end(); }
  const_iterator end() const { return _btree.end(); }
  iterator rbegin() { return _btree.rbegin(); }
  const_iterator rbegin() const { return _btree.rbegin(); };
  iterator rend() { return _btree.rend(); }
  const_iterator rend() const { return _btree.rend(); }

  /* Capacity */
  bool empty() const { return _btree.empty(); }
  size_type size() const { return _btree.size(); }
  size_type max_size() const { return _btree.max_size(); }

  /* Access Element */
  mapped_type& operator[](const key_type& k) {
    return (*((this->insert(make_pair(k, mapped_type()))).first)).second;
  }

  /* Modifiers */
  pair< iterator, bool > insert(const value_type& val) {
    return (_btree.insert(val));
  }
  iterator insert(iterator position, const value_type& val) {
    return (_btree.insert(position, val));
  }

  template < class InputIterator >
  void insert(InputIterator first, InputIterator last) {
    return (_btree.insert(first, last));
  }
  void erase(iterator position) { return (_btree.erase(position)); }
  size_type erase(const key_type& k) {
    return (_btree.erase(ft::make_pair(k, mapped_type())));
  }
  void erase(iterator first, iterator last) {
    return (_btree.erase(first, last));
  }

  void clear() { _btree.clear(); }
  void swap(map& x) { _btree.swap(x._btree); }

  key_compare key_comp() const { return (key_compare()); }
  value_compare value_comp() const { return value_compare(key_compare()); }
  size_type count(const key_type& k) const {
    if (_btree.find(k))
      return (1);
    else
      return (0);
  }
  allocator_type get_allocator() const { return (allocator_type()); }

  pair< const_iterator, const_iterator > equal_range(const key_type& k) const {
    return make_pair< const_iterator, const_iterator >(lower_bound(k),
                                                       upper_bound(k));
  }
  pair< iterator, iterator > equal_range(const key_type& k) {
    return make_pair< iterator, iterator >(lower_bound(k), upper_bound(k));
  }

  iterator lower_bound(const key_type& k) {
    iterator it = begin();
    while (_comp(*it, k) && it != end()) ++it;
    return (it);
  }
  const_iterator lower_bound(const key_type& k) const {
    const_iterator it = begin();
    while (_comp(*it, k) && it != end()) ++it;
    return (it);
  }

  iterator upper_bound(const key_type& k) {
    iterator it = begin();
    while (!_comp(*it, k) && it != end()) ++it;
    return (it);
  }
  const_iterator upper_bound(const key_type& k) const {
    const_iterator it = begin();
    while (!_comp(*it, k) && it != end()) ++it;
    return (it);
  }
};

template < class Key, class T, class Compare, class Alloc >
void swap(map< Key, T, Compare, Alloc >& x, map< Key, T, Compare, Alloc >& y) {
  x.swap(y);
};

template < class Key, class T, class Compare, class Alloc >
bool operator==(const ft::map< Key, T, Compare, Alloc >& lhs,
                const ft::map< Key, T, Compare, Alloc >& rhs) {
  if (lhs.size() != rhs.size()) return (false);
  return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}
template < class Key, class T, class Compare, class Alloc >
bool operator!=(const ft::map< Key, T, Compare, Alloc >& lhs,
                const ft::map< Key, T, Compare, Alloc >& rhs) {
  return !(lhs == rhs);
}
template < class Key, class T, class Compare, class Alloc >
bool operator<(const ft::map< Key, T, Compare, Alloc >& lhs,
               const ft::map< Key, T, Compare, Alloc >& rhs) {
  return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                      rhs.end()));
}
template < class Key, class T, class Compare, class Alloc >
bool operator<=(const ft::map< Key, T, Compare, Alloc >& lhs,
                const ft::map< Key, T, Compare, Alloc >& rhs) {
  return (!(rhs < lhs));
}
template < class Key, class T, class Compare, class Alloc >
bool operator>(const ft::map< Key, T, Compare, Alloc >& lhs,
               const ft::map< Key, T, Compare, Alloc >& rhs) {
  return (rhs < lhs);
}
template < class Key, class T, class Compare, class Alloc >
bool operator>=(const ft::map< Key, T, Compare, Alloc >& lhs,
                const ft::map< Key, T, Compare, Alloc >& rhs) {
  return (!(lhs < rhs));
}
}  // namespace ft
#endif
