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
		std::cout << "std::vector::max_size() = " << std_v1.max_size() << std::endl;
		std::cout << "ft::vector::max_size() = " << ft_v1.max_size() << std::endl;
		std::cout << "std::allocator::max_size() = " << alloc1.max_size() << std::endl;
		std::cout << "std::vector::capacity() = " << std_v1.capacity() << std::endl;
		std::cout << "ft::vector::capacity() = " << ft_v1.capacity() << std::endl;
		std_v1.push_back(23);
		std_v1.push_back(12);
		std_v1.push_back(7);
		std_v1.push_back(989);
		std_v1.push_back(7);

		std::cout << "std::vector::capacity() = " << std_v1.capacity() << std::endl;
		ft_v1.push_back(1);
		ft_v1.push_back(7);
		ft_v1.push_back(12);
		ft_v1.push_back(23);
		ft_v1.push_back(324);
		std::cout << "ft::vector::capacity() = " << ft_v1.capacity() << std::endl;
		std_v1.resize(std_v1.max_size() + 1);
	}
	catch ( std::exception& e )
	{
		std::cout << "Length error: " << e.what() << std::endl;
	}
}
