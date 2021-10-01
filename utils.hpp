#if !defined(UTILS_HPP)
#define UTILS_HPP
namespace ft
{
  template <bool, typename T = void>
  struct enable_if
  {
  };
  template <typename T>
  struct enable_if<true, T>
  {
    typedef T type;
  };
  template <class T>
  struct is_integral
  {
    static const bool value = false;
  };
  template <>
  struct is_integral<bool>
  {
    static const bool value = true;
  };
  template <>
  struct is_integral<char>
  {
    static const bool value = true;
  };
  // template <>
  // struct is_integral< char16_t > {
  //   static const bool value = true;
  // };
  // template <>
  // struct is_integral< char32_t > {
  //   static const bool value = true;
  // };
  template <>
  struct is_integral<wchar_t>
  {
    static const bool value = true;
  };
  template <>
  struct is_integral<signed char>
  {
    static const bool value = true;
  };
  template <>
  struct is_integral<short int>
  {
    static const bool value = true;
  };
  template <>
  struct is_integral<int>
  {
    static const bool value = true;
  };
  template <>
  struct is_integral<long int>
  {
    static const bool value = true;
  };
  template <>
  struct is_integral<long long int>
  {
    static const bool value = true;
  };
  template <>
  struct is_integral<unsigned char>
  {
    static const bool value = true;
  };
  template <>
  struct is_integral<unsigned short int>
  {
    static const bool value = true;
  };
  template <>
  struct is_integral<unsigned int>
  {
    static const bool value = true;
  };
  template <>
  struct is_integral<unsigned long int>
  {
    static const bool value = true;
  };
  template <>
  struct is_integral<unsigned long long int>
  {
    static const bool value = true;
  };
  template <typename T1, typename T2>
  struct pair
  {
  private:
    typedef T1 first_type;
    typedef T2 second_type;

  public:
    first_type first;
    second_type second;

    pair()
    {
      (void)this->first;
      (void)this->second;
    }
    pair(const first_type &a, const second_type &b)
    {
      this->first = a;
      this->second = b;
    }
    pair(const pair<T1, T2> &pr)
    {
      this->first = pr.first;
      this->second = pr.second;
    }

    pair &operator=(const pair &pr)
    {
      this->first = pr.first;
      this->second = pr.second;
      return *this;
    }
  };

  template <class T1, class T2>
  pair<T1, T2> make_pair(T1 x, T2 y)
  {
    return (pair<T1, T2>(x, y));
  }
  template <class T1, class T2>
  bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
  {
    return lhs.first == rhs.first && lhs.second == rhs.second;
  }

  template <class T1, class T2>
  bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
  {
    return !(lhs == rhs);
  }

  template <class T1, class T2>
  bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
  {
    return lhs.first < rhs.first ||
           (!(rhs.first < lhs.first) && lhs.second < rhs.second);
  }

  template <class T1, class T2>
  bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
  {
    return !(rhs < lhs);
  }

  template <class T1, class T2>
  bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
  {
    return rhs < lhs;
  }

  template <class T1, class T2>
  bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
  {
    return !(lhs < rhs);
  }
  template <bool flag, class IsTrue, class IsFalse>
  struct choose;

  template <class IsTrue, class IsFalse>
  struct choose<true, IsTrue, IsFalse>
  {
    typedef IsTrue type;
  };
  template <class IsTrue, class IsFalse>
  struct choose<false, IsTrue, IsFalse>
  {
    typedef IsFalse type;
  };

  template <class InputIterator1, class InputIterator2>
  bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
  {
    while (first1 != last1)
    {
      if (!(*first1 == *first2))
        return (false);
      ++first1;
      ++first2;
    }
    return (true);
  }
  template <class InputIterator1, class InputIterator2, class BinaryPredicate>
  bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2,
             BinaryPredicate pred)
  {
    while (first1 != last1)
    {
      if (!pred(*first1, *first2))
        return (false);
      ++first1;
      ++first2;
    }
    return (true);
  }

  template <class InputIterator1, class InputIterator2>
  bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
                               InputIterator2 first2, InputIterator2 last2)
  {
    while (first1 != last1)
    {
      if (first2 == last2 || *first2 < *first1)
        return false;
      else if (*first1 < *first2)
        return true;
      ++first1;
      ++first2;
    }
    return (first2 != last2);
  };

  template <class InputIterator1, class InputIterator2, class Compare>
  bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
                               InputIterator2 first2, InputIterator2 last2,
                               Compare comp)
  {
    while (first1 != last1)
    {
      if (first2 == last2 || comp(*first2, *first1))
        return false;
      else if (comp(*first1, *first2))
        return true;
      ++first1;
      ++first2;
    }
    return (first2 != last2);
  };
} // namespace ft

#endif // UTILS_HPP