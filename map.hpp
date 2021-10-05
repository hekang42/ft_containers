#ifndef MAP_HPP
#define MAP_HPP
#include <memory>

#include "MapIterator.hpp"
#include "iterator.hpp"
#include "utils.hpp"
#include "BTree.hpp"
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
  typedef typename ft::BTree< value_type, value_compare, allocator_type >::iterator iterator;
  typedef typename ft::BTree< value_type, value_compare, allocator_type >::const_iterator const_iterator;
  typedef ft::reverse_iterator< iterator > reverse_iterator;
  typedef ft::reverse_iterator< const_iterator > const_reverse_iterator;
  typedef
      typename ft::iterator_traits< iterator >::difference_type difference_type;
  typedef typename allocator_type::size_type size_type;

 private:
  key_compare _comp;
  allocator_type _alloc;
  size_type _size;
  BTree< value_type, value_compare, allocator_type>* _btree;

 public:
  /* Construct Map */
  /* empty (1) */
  explicit map(const key_compare& comp = key_compare(),
               const allocator_type& alloc = allocator_type()){
	
  };
  /* range (2) */
  template < class InputIterator >
  map(InputIterator first, InputIterator last,
      const key_compare& comp = key_compare(),
      const allocator_type& alloc = allocator_type());
  /* copy (3) */
  map(const map& x);

  map(/* args*/);
  map(const map& other){};
  map& operator=(const map& other){};
  ~map();

  /* single element (1) */
  pair< iterator, bool > insert(const value_type& val);
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
