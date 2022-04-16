#ifndef STACK_STRUCT_HPP
# define STACK_STRUCT_HPP

# include "global.hpp"
# include "stack.hpp"
# include "vector.hpp"

# include <stack>
# include <vector>
# include <deque>
# include <list>

typedef std::deque<int>						deque_type;
typedef std::list<int>						list_type;

typedef NAMESPACE::vector<int>				vector_type;

typedef NAMESPACE::stack<int, vector_type>	vstack_type;
typedef NAMESPACE::stack<int, deque_type>	dstack_type;
typedef NAMESPACE::stack<int, list_type>	lstack_type;

typedef NAMESPACE::stack<std::string>		string_stack_type;

#endif
