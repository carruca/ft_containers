#include "vector.hpp"
#include "global.hpp"
#include "utils.hpp"
#include "struct.hpp"

#include <iostream>
#include <algorithm>
#include <vector>

void	vector_swap( void )
{
	vector_type	v1(5, 23), v2(4, 2), v3, v4;

	v1.swap(v2);
	v3.swap(v2);
	v3.swap(v4);

	for (int i = 1; i < 10; (i *= 2))
		v3.push_back(i);

	NAMESPACE::swap(v3, v4);

	for_each(v1.begin(), v1.end(), display<int>);
	std::cout << "size of const vector 1 after swap = " << v1.size() << std::endl;
	std::cout << "max_size of const vector 1 after swap = " << v1.max_size() << std::endl;
	std::cout << "capacity of const vector 1 after swap = " << v1.capacity() << std::endl;

	for_each(v2.begin(), v2.end(), display<int>);
	std::cout << "size of const vector 2 after swap = " << v2.size() << std::endl;
	std::cout << "max_size of const vector 2 after swap = " << v2.max_size() << std::endl;
	std::cout << "capacity of const vector 2 after swap = " << v2.capacity() << std::endl;

	for_each(v3.begin(), v3.end(), display<int>);
	std::cout << "size of const vector 3 after swap = " << v3.size() << std::endl;
	std::cout << "max_size of const vector 3 after swap = " << v3.max_size() << std::endl;
	std::cout << "capacity of const vector 3 after swap = " << v3.capacity() << std::endl;

	for_each(v4.begin(), v4.end(), display<int>);
	std::cout << "size of const vector 4 after swap = " << v4.size() << std::endl;
	std::cout << "max_size of const vector 4 after swap = " << v4.max_size() << std::endl;
	std::cout << "capacity of const vector 4 after swap = " << v4.capacity() << std::endl;
}

