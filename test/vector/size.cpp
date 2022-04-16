#include "vector.hpp"
#include "global.hpp"
#include "utils.hpp"
#include "struct.hpp"

#include <iostream>
#include <algorithm>
#include <vector>

void	vector_resize( void )
{
	std::allocator<int>	a1;
	vector_type			v1(a1);

	std::cout << "sizeof vector = " << sizeof(v1) << std::endl;
	std::cout << "sizeof std::allocator = " << sizeof(a1) << std::endl;
	std::cout << "max_size of vector = " << v1.max_size() << std::endl;
	std::cout << "max_size of std::allocator = " << a1.max_size() << std::endl;
	std::cout << "capacity of vector = " << v1.capacity() << std::endl;

	v1.push_back(23);
	v1.push_back(12);
	v1.push_back(7);
	v1.push_back(989);
	v1.push_back(7);
	v1.push_back(1);
	v1.push_back(7);
	v1.push_back(12);
	v1.push_back(23);
	v1.push_back(324);

	std::cout << "capacity of vector = " << v1.capacity() << std::endl;

	vector_type			v2(v1.begin(), v1.end());

	try
	{
		v2.resize(v2.max_size() + 1);
	}
	catch ( std::exception& e )
	{
		std::cout << "Length error: " << e.what() << std::endl;
	}

	for_each(v2.begin(), v2.end(), display<int>);

	v2.resize(2);
	v2.resize(18);
	v2.resize(7);
	for_each(v2.begin(), v2.end(), display<int>);

	std::cout << "capacity of vector = " << v2.capacity() << std::endl;
}
