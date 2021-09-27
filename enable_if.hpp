#ifndef ENABLE_IF_HPP
#define ENABLE_IF_HPP
template < bool Cond, class T = void >
struct enable_if {
	typedef T type;
};

#endif