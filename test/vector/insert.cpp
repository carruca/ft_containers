#include "vector.hpp"
#include "global.hpp"
#include "utils.hpp"
#include "struct.hpp"

#include <iostream>
#include <algorithm>
#include <vector>

void	vector_insert( void )
{
	string_vector_type	v1;
	string_vector_type	v2;
	string_vector_type	v3;
	string_vector_type	v4;

	v1.push_back("hola");
	v1.push_back("que");
	v1.push_back("tal");
	v1.push_back("estas");
	v1.push_back("yo");
	v1.push_back("bien");
	v1.push_back("en");
	v1.push_back("casa");

	v2.push_back("yo");
	v2.push_back("estoy");
	v2.push_back("bien");

	v4.insert(v4.begin(), v2.begin(), v2.end());

	v3 = v1;
	v1.resize(4);
	v3.reserve(100);

	string_vector_iterator	start3(v3.begin());

	v3.insert(start3 + 7, "yyyyyy");

	std::cout << "size of vector 1 = " << v1.size() << std::endl;
	std::cout << "capacity of vector 1 = " << v1.capacity() << std::endl;
	std::cout << "size of vector 2 = " << v2.size() << std::endl;
	std::cout << "capacity of vector 2 = " << v2.capacity() << std::endl;
	std::cout << "size of vector 3 = " << v3.size() << std::endl;
	std::cout << "capacity of vector 3 = " << v3.capacity() << std::endl;
	std::cout << "size of vector 4 = " << v4.size() << std::endl;
	std::cout << "capacity of vector 4 = " << v4.capacity() << std::endl;

	for_each(v1.begin(), v1.end(), display<std::string>);
	for_each(v2.begin(), v2.end(), display<std::string>);
	for_each(v3.begin(), v3.end(), display<std::string>);
	for_each(v4.begin(), v4.end(), display<std::string>);

	string_vector_iterator	start(v1.begin());

	v1.insert(start + 1, 17, "e");

	std::cout << "size of vector 1 = " << v1.size() << std::endl;
	std::cout << "capacity of vector 1 = " << v1.capacity() << std::endl;
	for_each(v1.begin(), v1.end(), display<std::string>);

	v1.erase(v1.begin());

	for_each(v1.begin(), v1.end(), display<std::string>);
	std::cout << "size of vector 1 after erase in insert = " << v1.size() << std::endl;
}
