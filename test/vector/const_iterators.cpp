#include "vector.hpp"
#include "global.hpp"
#include "utils.hpp"
#include "struct.hpp"

#include <iostream>
#include <algorithm>
#include <vector>

void	vector_const_iterators( void )
{
	vector_type			v1(12, 45);
	const vector_type	v2;
	const vector_type	v3(v1);
	const vector_type	v4(4, 42, v2.get_allocator());

	v1.push_back(23);
	v1.push_back(12);
	v1.push_back(7);
	v1.push_back(989);
	v1.push_back(7);

	std::cout << "vector 1 desplay" << std::endl;
	for_each(v1.begin(), v1.end(), display<int>);
	std::cout << "vector 3 desplay" << std::endl;
	for_each(v3.begin(), v3.end(), display<int>);
	std::cout << "vector 4 desplay" << std::endl;
	for_each(v4.begin(), v4.end(), display<int>);
	std::cout << "vector 2 desplay" << std::endl;
	for_each(v2.begin(), v2.end(), display<int>);

	std::cout << "size of const vector 3 = " << v3.size() << std::endl;
	std::cout << "max_size of const vector 3 = " << v3.max_size() << std::endl;
	std::cout << "capacity of const vector 3 = " << v3.capacity() << std::endl;
	std::cout << "vector 2 is " << (v2.empty() ? "empty" : "not empty") << std::endl;
	std::cout << "size of const vector 1 = " << v3.size() << std::endl;
	std::cout << "third position of const vector 1 = " << v1[3] << std::endl;

	try
	{
		std::cout << "forth position of const vector 1 = " << v1.at(15) << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout  << "exception thow from vector 1 at function = " << e.what() << std::endl;
	}

	std::cout << "front vector 1 = " << v1.front() << std::endl;
	std::cout << "back vector 1 = " << v1.back() << std::endl;
}
