#include "stack.hpp"
#include "vector.hpp"
#include "struct.hpp"

#include <stack>
#include <vector>
#include <iostream>

void	stack_size( void )
{
	deque_type		d1;
	dstack_type		s1(d1);

	for (int i = 0; i < 100; i += 2)
		s1.push(i);

	std::cout << "stack size = " << s1.size() << std::endl;
}
