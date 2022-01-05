#include <iostream>
#include <algorithm>
#include <vector>
#include <stdexcept>
#include <list>
#include "ft_vector.hpp"

void	default_constructor_test( void )
{
	std::vector<int>	vect_std;
	ft::vector<int>		vect_ft;

	if ((vect_std.begin() == vect_std.end() && vect_std.capacity() == 0)
		& (vect_ft.begin() == vect_ft.end() && vect_ft.capacity() == 0))
	{
		std::cout << "Default constructor is corrected" << std::endl;
	}
	else
		std::cout << "Default constructor is wrong" << std::endl;
}

void	explicit_constructor_test( void )
{
	
}
