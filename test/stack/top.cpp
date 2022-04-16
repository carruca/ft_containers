#include "stack.hpp"
#include "vector.hpp"
#include "struct.hpp"

#include <stack>
#include <vector>
#include <iostream>

void	stack_pop( void )
{

	vector_type		v1;

//	v1.push_back(34);
//	v1.push_back(81);

	vstack_type		s1;

	for (int i = 0; i < 300; ++i)
		s1.push(i);

	vstack_type		s2(vector_type);
	vstack_type		s3;

	s3 = s1;

	std::cout << "stack 3 is " << (s1.empty() ? "empty" : "not empty") << " before pop" << std::endl;

	for (int i = 0; i < 300; ++i)
		s1.pop();

	std::cout << "stack 3 is " << (s1.empty() ? "empty" : "not empty") << " after pop" << std::endl;
}
