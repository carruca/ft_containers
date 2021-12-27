#include <iostream>
#include <vector>
#include <stdexcept>
#include "ft_vector.hpp"

void	testVector(void)
{
	try
	{
		std::vector<int>	std_v1;
		ft::vector<int>		ft_v1;
		std::allocator<int>	alloc1;

		std::cout << "Size of empty std::vector = " << sizeof(std_v1) << std::endl;
		std::cout << "Size of empty ft::vector = " << sizeof(ft_v1) << std::endl;
		std::cout << "Size of empty std::allocator = " << sizeof(alloc1) << std::endl;
		std_v1.resize(std_v1.max_size() + 1);
	}
	catch ( std::exception& e )
	{
		std::cout << "Length error: " << e.what() << std::endl;
	}
}
