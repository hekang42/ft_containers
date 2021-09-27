#include <iostream>  // std::cout
#include <iterator>  // std::iterator_traits
#include <typeinfo>  // typeid
#include <vector>

#include "iterator.hpp"

int main() {
  // iterator
  typedef std::iterator_traits< int* > traits;
  if (typeid(traits::iterator_category) ==
      typeid(std::random_access_iterator_tag))
    std::cout << "int* is a random-access iterator";
	std::cout << std::endl;

  {
    std::vector< int > myvector;
    for (int i = 0; i < 10; i++) myvector.push_back(i);

    typedef std::vector< int >::iterator iter_type;
    iter_type from(myvector.begin());
    iter_type until(myvector.end());
    ft::reverse_iterator< iter_type > rev_until(from);
    ft::reverse_iterator< iter_type > rev_from(until);

    std::cout << "myvector:";
    while (rev_from != rev_until) std::cout << ' ' << *rev_from++;
    std::cout << std::endl;
  }
  return 0;
}