// #include <iostream>  // std::cout
// // #include <iterator>  // std::iterator_traits
// // #include <type_traits>
// // #include <typeinfo>  // typeid
// // #include <vector>

// #include "is_integral.hpp"
// #include "iterator.hpp"

// // int main() {
// //   // iterator
// //   typedef std::iterator_traits< int* > traits;
// //   if (typeid(traits::iterator_category) ==
// //       typeid(std::random_access_iterator_tag))
// //     std::cout << "int* is a random-access iterator";
// // 	std::cout << std::endl;

// //   {
// //     std::vector< int > myvector;
// //     for (int i = 0; i < 10; i++) myvector.push_back(i);

// //     typedef std::vector< int >::iterator iter_type;
// //     iter_type from(myvector.begin());
// //     iter_type until(myvector.end());
// //     ft::reverse_iterator< iter_type > rev_until(from);
// //     ft::reverse_iterator< iter_type > rev_from(until);

// //     std::cout << "myvector:";
// //     while (rev_from != rev_until) std::cout << ' ' << *rev_from++;
// //     std::cout << std::endl;
// //   }
// //   return 0;
// // }

// class A {};

// int main() {
//   std::cout << std::boolalpha;
//   std::cout << "is_integral:" << std::endl;
// //   std::cout << "char: " << std::is_integral< char >::value << std::endl;
// //   std::cout << "int: " << std::is_integral< int >::value << std::endl;
// //   std::cout << "float: " << std::is_integral< float >::value << std::endl;
//   std::cout << "char: " << ft::is_integral< char >::value << std::endl;
//   std::cout << "int: " << ft::is_integral< int >::value << std::endl;
//   std::cout << "float: " << ft::is_integral< float >::value << std::endl;
//   std::cout << "float: " << ft::is_integral< float >::value << std::endl;
//   return 0;
// }

// #include <algorithm>  // std::equal
// #include <iostream>   // std::cout
// #include <vector>     // std::vector
#include "utils.hpp"

// bool mypredicate(int i, int j) { return (i == j); }

// int main() {
//   int myints[] = {20, 40, 60, 80, 100};             //   myints: 20 40 60 80 100
//   std::vector< int > myvector(myints, myints + 5);  // myvector: 20 40 60 80 100

//   // using default comparison:
//   if (ft::equal(myvector.begin(), myvector.end(), myints))
//     std::cout << "The contents of both sequences are equal.\n";
//   else
//     std::cout << "The contents of both sequences differ.\n";

//   myvector[3] = 81;  // myvector: 20 40 60 81 100

//   // using predicate comparison:
//   if (ft::equal(myvector.begin(), myvector.end(), myints, mypredicate))
//     std::cout << "The contents of both sequences are equal.\n";
//   else
//     std::cout << "The contents of both sequences differ.\n";

//   return 0;
// }

// lexicographical_compare example
#include <iostream>     // std::cout, std::boolalpha
#include <algorithm>    // std::lexicographical_compare
#include <cctype>       // std::tolower

// a case-insensitive comparison function:
bool mycomp (char c1, char c2)
{ return std::tolower(c1)<std::tolower(c2); }

int main () {
  char foo[]="Apple";
  char bar[]="apartment";

  std::cout << std::boolalpha;

  std::cout << "Comparing foo and bar lexicographically (foo<bar):\n";

  std::cout << "Using default comparison (operator<): ";
  std::cout << ft::lexicographical_compare(foo,foo+5,bar,bar+9);
  std::cout << '\n';

  std::cout << "Using mycomp as comparison object: ";
  std::cout << ft::lexicographical_compare(foo,foo+5,bar,bar+9,mycomp);
  std::cout << '\n';

  return 0;
}