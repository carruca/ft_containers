#ifndef VECTOR_STRUCT_HPP
# define VECTOR_STRUCT_HPP

# include "global.hpp"
# include "vector.hpp"

# include <vector>

typedef NAMESPACE::vector<int>				vector_type;
typedef vector_type::iterator				vector_iterator;
typedef vector_type::reverse_iterator		vector_reverse_iterator;
typedef vector_type::const_iterator			vector_const_iterator;

typedef NAMESPACE::vector<std::string>		string_vector_type;
typedef string_vector_type::iterator		string_vector_iterator;
typedef string_vector_type::const_iterator	string_vector_const_iterator;

class	foo
{
public:
	foo(void)
	{
		std::cout << "class foo constructor called" << std::endl;
	}
	~foo(void)
	{
		std::cout << "class foo destructor called" << std::endl;
	}
};

typedef NAMESPACE::vector<foo>				foo_vector_type;
typedef string_vector_type::iterator		foo_vector_iterator;
typedef string_vector_type::const_iterator	foo_vector_const_iterator;

#endif
