#include "vector.hpp"
#include "global.hpp"
#include "utils.hpp"
#include "struct.hpp"

#include <iostream>
#include <algorithm>
#include <vector>

void	vector_assign( void )
{
	vector_type		v1;
	vector_type		v2(v1.get_allocator());
	vector_type		v3;
	vector_type		v4;

	v1.assign(3, 12);
	v2.assign(400000, 300);
	v3.assign(v1.begin(), v1.end());
	v4.assign(100 + v2.begin(), v2.end());

	if (v1.size() == v3.size())
		std::cout << "after assign both vectors are equal size" << std::endl;
	if (v2.size() != v4.size())
		std::cout << "after assign both vectors are diferent size" << std::endl;

	for_each(v1.begin(), v1.end(), display<int>);
	for_each(v4.begin(), v4.end(), display<int>);

	v2.erase(v2.begin(), v2.end());

	std::cout << "vector 2 is " << (v2.empty() ? "empty" : "not empty") << std::endl;
}
