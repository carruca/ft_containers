#include "lexicographical_compare.hpp"

#include <algorithm>
#include <vector>
#include <iostream>

bool	cmp( char c1, char c2 )
{
	return c1 < c2;
}

void	test_lexicographical_compare( void )
{
	char				a[] = { 'a', 'b', 'c', 'd', 'e' };
	std::vector<char>	v1(	a, a + 5 );
	std::vector<char>	v2( v1 );

	std::cout << std::endl << "* utils: lexicographical_compare TEST *" << std::endl;

	if ( std::lexicographical_compare( v1.begin(), v1.end(), v2.begin(), v2.end() )
			== ft::lexicographical_compare( v1.begin(), v1.end(), v2.begin(), v2.end() ))
			std::cout << "Both vectors are equal:			CHECK!" << std::endl;
	else
			std::cout << "Both vectors are equal:			WRONG!" << std::endl;

	v1[2] = 'f';

	if ( std::lexicographical_compare( v1.begin(), v1.end(), v2.begin(), v2.end(), cmp )
			== ft::lexicographical_compare( v1.begin(), v1.end(), v2.begin(), v2.end(), cmp ))
			std::cout << "Both vectors differ:			CHECK!" << std::endl;
	else
			std::cout << "Both vectors differ:			WRONG!" << std::endl;
}
