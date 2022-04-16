#include "stack.hpp"
#include "vector.hpp"
#include "struct.hpp"

#include <stack>
#include <vector>
#include <iostream>

void	stack_relationals( void )
{
	
	lstack_type		s1;

	for (int i = 0; i < 200; ++i)
		s1.push(i);

	lstack_type		s2;

	for (int i = 0; i < 200; ++i)
		s2.push(i);

	std::cout << "stack 1 and stack 2 are " << (s1 == s2 ? "equal" : "diferent") << std::endl;

	std::cout << "size of stack 1 = " << s1.size() << std::endl;

	lstack_type		s3;

	for (int i = 1; i < 500; i *= 3)
		s3.push(i);
	
	s2 = s3;

	std::cout << "stack 1 is " << (s1 < s3 ? "smaller" : "not smaller") << " than stack 3" << std::endl;
	std::cout << "stack 1 and stack 2 are " << (s1 == s2 ? "equal" : "diferent") << std::endl;
	std::cout << "stack 1 and stack 3 are " << (s1 != s3 ? "diferent" : "equal") << std::endl;
	std::cout << "stack 3 is " << (s3 >= s2 ? "bigger or equal" : "not bigger or equal") << " than stack 2" << std::endl;
}
