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
 private:
  /* data */
 public:
  typedef Key key_type;
  typedef T mapped_type;
  typedef pair< const key_type, mapped_type > value_type;
  typedef Compare key_compare;

  class value_compare {
   protected:
    Compare comp;

   public:
    value_compare(Compare c) : comp(c) {}
    // typedef bool result_type;
    // typedef value_type first_argument_type;
    // typedef value_type second_argument_type;
    bool operator()(const value_type& x, const value_type& y) const {
      return comp(x.first, y.first);
    }
  };

  typedef Alloc allocator_type;
  typedef typename allocator_type::reference reference;
  typedef typename allocator_type::const_reference const_reference;
  typedef typename allocator_type::pointer pointer;
  typedef typename allocator_type::const_pointer const_pointer;
  typedef
      typename ft::BTree< value_type, value_compare, allocator_type >::iterator
          iterator;
  typedef typename ft::BTree< value_type, value_compare,
                              allocator_type >::const_iterator const_iterator;
  typedef ft::reverse_iterator< iterator > reverse_iterator;
  typedef ft::reverse_iterator< const_iterator > const_reverse_iterator;
  typedef
      typename ft::iterator_traits< iterator >::difference_type difference_type;
  typedef typename allocator_type::size_type size_type;

  typedef typename Alloc::template rebind<
      BTree< value_type, value_compare, allocator_type > >::other AlTree;
  typedef typename BTree< value_type, value_compare, allocator_type >::TreeNode
      TreeNode;

 private:
  key_compare _comp;
  allocator_type _alloc;
  size_type _size;
  BTree< value_type, value_compare, allocator_type >* _btree;

 public:
  /* Construct Map */
  /* empty (1) */
  explicit map(const key_compare& comp = key_compare(),
               const allocator_type& alloc = allocator_type())
      : _comp(comp), _alloc(alloc), _size(0) {
    AlTree _treealloc;
    this->_btree = _treealloc.allocate(1);
    _treealloc.construct(this->_btree,
                         BTree< value_type, value_compare, allocator_type >(
                             value_compare(this->_comp)));
  };
  /* range (2) */
  template < class InputIterator >
  map(InputIterator first, InputIterator last,
      const key_compare& comp = key_compare(),
      const allocator_type& alloc = allocator_type())
      : _comp(comp), _alloc(alloc), _size(0) {
    AlTree _treeAlloc;
    this->_btree = _treeAlloc.allocate(1);
    _treeAlloc.construct(this->_btree,
                         BTree< value_type, value_compare, allocator_type >(
                             value_compare(this->_comp)));
    this->insert(first, last);
  };
  /* copy (3) */
  map(const map& x) : _comp(x._comp), _alloc(x._alloc), _size(x._size) {
    AlTree _treeAlloc;
    this->_tree = _treeAlloc.allocate(1);
    _treeAlloc.construct(this->_btree, *(x._tree));
  };

  map& operator=(const map& other) {
    if (this != other) {
      *(this->_btree) = *(other._btree);
      this->size = other._size;
    }
    return (*this);
  }
  ~map() {
    AlTree _treeAlloc;
    _treeAlloc.destroy(this->_tree);
    _treeAlloc.deallocate(this->_tree, 1);
  };

  /* single element (1) */
  pair< iterator, bool > insert(const value_type& val) {
    pair< TreeNode*, bool > ret = this->_btree->insert(val);
    if (ret.second == true) {
      ++this->_size;
        return (pair<iterator, bool>(iterator(ret.first, this->_btree), true)));
    } else {
        return (pair<iterator, bool>(iterator(ret.first, this->_btree), false)));
    }
  }
  /* with hint (2) */
  iterator insert(iterator position, const value_type& val);
  /* range (3) */
  template < class InputIterator >
  void insert(InputIterator first, InputIterator last);
};

template < class T >
struct less : binary_function< T, T, bool > {
  bool operator()(const T& x, const T& y) const { return x < y; }
};

}  // namespace ft

#endif
