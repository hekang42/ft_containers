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
// #include <iostream>     // std::cout, std::boolalpha
// #include <algorithm>    // std::lexicographical_compare
// #include <cctype>       // std::tolower

// // a case-insensitive comparison function:
// bool mycomp (char c1, char c2)
// { return std::tolower(c1)<std::tolower(c2); }

// int main () {
//   char foo[]="Apple";
//   char bar[]="apartment";

//   std::cout << std::boolalpha;

//   std::cout << "Comparing foo and bar lexicographically (foo<bar):\n";

//   std::cout << "Using default comparison (operator<): ";
//   std::cout << ft::lexicographical_compare(foo,foo+5,bar,bar+9);
//   std::cout << '\n';

//   std::cout << "Using mycomp as comparison object: ";
//   std::cout << ft::lexicographical_compare(foo,foo+5,bar,bar+9,mycomp);
//   std::cout << '\n';

//   return 0;
// }

// #include <vector>
// #include <iostream>
// using namespace std;
// int main()
// {
//     vector<int> v1;
//     v1.push_back(10);
//     v1.push_back(20);
//     v1.push_back(30);
//     v1.push_back(40);

//     vector<int> v2;
    
//      v2.push_back(100);
//      v2.push_back(200);
//      v2.push_back(300);
//      v2.push_back(300);
//      v2.push_back(300);
//      v2.push_back(300);
    
//     for(vector<int>::size_type i=0; i<v1.size(); i++)
//         cout << v1[i] << ", " << v2[i] << endl;
//     cout << endl;
    
//     v1.swap(v2); //v1과 v2를 스왑
    
//     for(vector<int>::size_type i=0; i<v1.size(); i++)
//         cout << v1[i] << ", " << v2[i] << endl;
//     cout << endl;
    
//     return 0;
// }

// vector::empty
// #include <iostream>
// #include <vector>
// #include "vector.hpp"

// int main ()
// {
//   ft::vector<int> myvector;
//   int sum (0);

//   for (int i=1;i<=10;i++) myvector.push_back(i);

//   while (!myvector.empty())
//   {
//      sum += myvector.back();
//      myvector.pop_back();
//   }

//   std::cout << "total: " << sum << '\n';

//   return 0;
// }

// #include <iostream>
// #include <vector>
// #include "vector.hpp"

// int main ()
// {
//   ft::vector<int> myvector;
//   int sum (0);
//   myvector.push_back (100);
//   myvector.push_back (200);
//   myvector.push_back (300);

//   while (!myvector.empty())
//   {
//     sum+=myvector.back();
//     myvector.pop_back();
//   }

//   std::cout << "The elements of myvector add up to " << sum << '\n';

//   return 0;
// }

// #include "vector.hpp"
// #include <list>
// #include <vector>
// #include <iostream>
// typedef std::vector<std::string> strlist;

// int	main()
// {
// 	strlist::iterator	it;
// 	strlist	sv(4, "asfd");
// 	ft::vector<strlist>	vec(4, sv);
// 	ft::vector<strlist>::iterator it2;
// 	it = (vec.begin())->begin();
	
// 	std::cout << *it << std::endl;
// 	return (0);
// }


#include <map>
#include <iostream>
int main ()
{
  std::map<char,int> mymap;

  // first insert function version (single parameter):
  mymap.insert ( std::pair<char,int>('a',100) );
  mymap.insert ( std::pair<char,int>('z',200) );

  std::pair<std::map<char,int>::iterator,bool> ret;
  ret = mymap.insert ( std::pair<char,int>('z',500) );
  
  if (ret.second==false) {
    std::cout << "element 'z' already existed";
    std::cout << " with a value of " << ret.first->second << '\n';
  }

  // second insert function version (with hint position):
  std::map<char,int>::iterator it = mymap.begin();
  mymap.insert (it, std::pair<char,int>('b',300));  // max efficiency inserting
  mymap.insert (it, std::pair<char,int>('c',400));  // no max efficiency inserting

  // third insert function version (range insertion):
  std::map<char,int> anothermap;
  anothermap.insert(mymap.begin(),mymap.find('c'));

  // showing contents:
  std::cout << "mymap contains:\n";
  for (it=mymap.begin(); it!=mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  std::cout << "anothermap contains:\n";
  for (it=anothermap.begin(); it!=anothermap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  return 0;
}


#include "BTree.hpp"
#include "utils.hpp"
int main()
{
	
	ft::BTree<ft::pair<int, std::string>, &_comp> btree;

}