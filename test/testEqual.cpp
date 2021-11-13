#include "ft_equal.hpp"
#include <algorithm>
#include <vector>
#include <iostream>


bool	pred( int x, int y )
{
	return x == y;
}

void	testEqual( void )
{
	int					a[] = { 10, 21, 22, 45, 12, 34 };
	std::vector<int>	v1( a, a + 5 );

	std::cout << std::endl << "* utils: equal TEST *" << std::endl;

	if ( std::equal( v1.begin(), v1.end(), a ) & ft::equal( v1.begin(), v1.end(), a ) )
		std::cout << "Contents are equal:			CHECK!" << std::endl;
	else
		std::cout << "Contents are differ:			WRONG!" << std::endl;

	v1[3] = 17;

	if ( !std::equal( v1.begin(), v1.end(), a, pred ) & !ft::equal( v1.begin(), v1.end(), a, pred ) )
		std::cout << "Contents are differ:			CHECK!" << std::endl;
	else
		std::cout << "Contents are equal:			WRONG!" << std::endl;
}
