#include "vector.hpp"
#include "global.hpp"
#include "utils.hpp"
#include "struct.hpp"

#include <iostream>
#include <algorithm>
#include <vector>

void	vector_reserve( void )
{
	string_vector_type	v1;

	v1.push_back("hola");
	v1.push_back("mi");
	v1.push_back("amor");
	v1.push_back("quiero");
	v1.push_back("hablar");
	v1.push_back("contigo");
	v1.push_back("estoy");
	v1.push_back("hecho");
	v1.push_back("un");
	v1.push_back("lio");
	
	try
	{
		v1.reserve(80);
		std::cout << "capacity of vector 1 after reserve = " << v1.capacity() << std::endl;
		v1.insert(v1.end(), 34, "comooooooooooo");
		for_each(v1.begin(), v1.end(), display<std::string>);
		v1.reserve(v1.max_size() + 1);
	}
	catch (std::exception &e)
	{
		std::cout << "Lenght max_size error in reserve: " << e.what() << std::endl;
	}

	string_vector_type	v2;
	string_vector_type	v3;
	string_vector_type	v4(v1);

	v3 = v4;

	NAMESPACE::swap(v2, v1);

	for_each(v2.begin(), v2.end(), display<std::string>);

	v2.clear();

	for_each(v2.begin(), v2.end(), display<std::string>);

	v2.insert(v2.begin(), v4.begin(), 3 + v4.begin());

	for_each(v2.begin(), v2.end(), display<std::string>);

	std::cout << "capacity of vector 4 after reverse = " << v4.capacity() << std::endl;
}
