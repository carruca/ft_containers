#include "vector.hpp"

#include <iostream>
#include <algorithm>
#include <vector>
#include <stdexcept>
#include <list>

void	vector_default_constructor( void )
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
