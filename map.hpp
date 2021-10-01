#ifndef MAP_HPP
#define MAP_HPP
#include "utils.hpp"
#include "VectorIterator.hpp"
#include "iterator.hpp"
namespace ft
{
  template <class Key,
            class T,
            class Compare = less<Key>,
            class Alloc = std::allocator<ft::pair<const Key, T> > >
  class map
  {
  private:
    /* data */
  public:
    typedef Key key_type;
    typedef T mapped_type;
    typedef pair<const key_type, mapped_type> value_type;
    typedef Compare key_compare ;
    
    typedef Alloc allocator_type;
    typedef typename allocator_type::reference reference;
    typedef typename allocator_type::const_reference const_reference;
    typedef typename allocator_type::pointer reference;
    typedef typename allocator_type::const_pointer const_reference;
    typedef ft::MapIterator<T, false> iterator;
    typedef ft::MapIterator<T, true> const_iterator;
    typedef ft::reverse_iterator<iterator> reverse_iterator;
    typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
    typedef typename iterator_traits<iterator>::difference_type difference_type;
    typedef typename allocator_type::size_type size_type;




    map(/* args*/);
    map(const map &other){};
    map &operator=(const map &other){};
    ~map();
  };

  template <class T>
  struct less : binary_function<T, T, bool>
  {
    bool operator()(const T &x, const T &y) const { return x < y; }
  };

}

#endif
