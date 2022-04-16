#include "vector.hpp"
#include "global.hpp"
#include "utils.hpp"
#include "struct.hpp"

#include <iostream>
#include <algorithm>
#include <vector>
#include <stdexcept>
#include <list>

void	vector_old_test(void)
{
	typedef std::vector<std::string>			stdVector_type;
	typedef ft::vector<std::string>				ftVector_type;

	std::cout << "std vector size = " << sizeof(stdVector_type) << std::endl;
	std::cout << "std vector size = " << sizeof(ftVector_type) << std::endl;

	std::vector<int>	std_vec_int1;
	std::vector<int>	std_vec_int2;
	ft::vector<int>		ft_vec_int1;
	std::string			str1;
	std::string			str2;

	std_vec_int1.assign(3, 12);
	std_vec_int1.assign(std_vec_int2.begin(), std_vec_int2.begin());
	for_each(std_vec_int1.begin(), std_vec_int1.end(), display<int>);

	ft_vec_int1.assign(3, 12);
	ft_vec_int1.assign(2, 4);
	ft_vec_int1.assign(3, 4);
	for_each(ft_vec_int1.begin(), ft_vec_int1.end(), display<int>);

	std::allocator<int>	alloc1;

	std::cout << "Size of empty std::vector = " << sizeof(std_vec_int1) << std::endl;
	std::cout << "Size of empty ft::vector = " << sizeof(ft_vec_int1) << std::endl;
	std::cout << "Size of empty std::allocator = " << sizeof(alloc1) << std::endl;
	std::cout << "std::vector::max_size() = " << std_vec_int1.max_size() << std::endl;
	std::cout << "ft::vector::max_size() = " << ft_vec_int1.max_size() << std::endl;
	std::cout << "std::allocator::max_size() = " << alloc1.max_size() << std::endl;
	std::cout << "std::vector::capacity() = " << std_vec_int1.capacity() << std::endl;
	std::cout << "ft::vector::capacity() = " << ft_vec_int1.capacity() << std::endl;
	std_vec_int1.push_back(23);
	std_vec_int1.push_back(12);
	std_vec_int1.push_back(7);
	std_vec_int1.push_back(989);
	std_vec_int1.push_back(7);

	std::cout << "std::vector::capacity() = " << std_vec_int1.capacity() << std::endl;
	ft_vec_int1.push_back(1);
	ft_vec_int1.push_back(7);
	ft_vec_int1.push_back(12);
	ft_vec_int1.push_back(23);
	ft_vec_int1.push_back(324);
	std::cout << "ft::vector::capacity() = " << ft_vec_int1.capacity() << std::endl;
	std::cout << "Size of ft::vector = " << sizeof(ft_vec_int1) << std::endl;
	try
	{
		std_vec_int1.resize(std_vec_int1.max_size() + 1);
	}
	catch ( std::exception& e )
	{
		std::cout << "Length error: " << e.what() << std::endl;
	}
	try
	{
		ft_vec_int1.resize(ft_vec_int1.max_size() + 1);
	}
	catch ( std::exception& e )
	{
		std::cout << "Length error: " << e.what() << std::endl;
	}

	for_each(std_vec_int1.begin(), std_vec_int1.end(), display<int>);
	for_each(ft_vec_int1.begin(), ft_vec_int1.end(), display<int>);
	std_vec_int1.resize(2);
	ft_vec_int1.resize(2);
	std::cout << "std::vector::capacity() = " << std_vec_int1.capacity() << std::endl;
	std::cout << "ft::vector::capacity() = " << ft_vec_int1.capacity() << std::endl;
	for_each(std_vec_int1.begin(), std_vec_int1.end(), display<int>);
	for_each(ft_vec_int1.begin(), ft_vec_int1.end(), display<int>);

	std::vector<int>	std_v2 = std_vec_int1;
	ft::vector<int>		ft_v2 = ft_vec_int1;

	std::cout << "assignment operator:" << std::endl;
	for_each(std_v2.begin(), std_v2.end(), display<int>);
	for_each(ft_v2.begin(), ft_v2.end(), display<int>);
	std::cout << "std::vector::capacity() = " << std_v2.capacity() << std::endl;
	std::cout << "ft::vector::capacity() = " << ft_v2.capacity() << std::endl;

	std::vector<std::string>	std_vec_string;
	ft::vector<std::string>		ft_vec_string;

	std_vec_string.push_back("hola");
	std_vec_string.push_back("que");
	std_vec_string.push_back("tal");
	std_vec_string.push_back("estas");
	std_vec_string.push_back("yo");
	std_vec_string.push_back("bien");
	std_vec_string.push_back("en");
	std_vec_string.push_back("casa");

	ft_vec_string.push_back("hola");
	ft_vec_string.push_back("que");
	ft_vec_string.push_back("tal");
	ft_vec_string.push_back("estas");
	ft_vec_string.push_back("yo");
	ft_vec_string.push_back("bien");
	ft_vec_string.push_back("en");
	ft_vec_string.push_back("casa");

	////////// VECTOR<INT> - insert tests //////////

	for_each(std_vec_string.begin(), std_vec_string.end(), display<std::string>);
	for_each(ft_vec_string.begin(), ft_vec_string.end(), display<std::string>);

	std::cout << "<<	std_vec_int1" << std::endl;
	std::cout << "std::vector::size() = " << std_vec_int1.size() << std::endl;
	std::cout << "std::vector::capacity() = " << std_vec_int1.capacity() << std::endl;
	std::vector<int>::iterator	it_int = std_vec_int1.begin();
//	std_vec_int1.insert(it_int, 0, 34);
	std::cout << "std_vec_int" << std::endl;
	for_each(std_vec_int1.begin(), std_vec_int1.end(), display<int>);
	std_vec_int1.insert(it_int + 1, 17, 34);
	std_vec_int1.push_back(18);
	//std_vec_int1.insert(it_int, 2, 2);
	std::cout << "std_vec_int" << std::endl;
	for_each(std_vec_int1.begin(), std_vec_int1.end(), display<int>);
	std::cout << "std::vector::size = " << std_vec_int1.size() << std::endl;
	std::cout << "std::vector::capacity = " << std_vec_int1.capacity() << std::endl;

	std::cout << "<<	ft_vec_int1" << std::endl;
	std::cout << "ft::vector::size = " << ft_vec_int1.size() << std::endl;
	std::cout << "ft::vector::capacity = " << ft_vec_int1.capacity() << std::endl;
	ft::vector<int>::iterator	ft_it_int = ft_vec_int1.begin();
//	ft_vec_int1.insert(ft_it_int, 0, 34);
	std::cout << "ft_vec_int" << std::endl;
	for_each(ft_vec_int1.begin(), ft_vec_int1.end(), display<int>);
	ft_vec_int1.insert(ft_it_int + 1, 17, 34);
	ft_vec_int1.push_back(18);
	//std_vec_int1.insert(ft_it_int, 2, 2);
	std::cout << "ft_vec_int" << std::endl;
	for_each(ft_vec_int1.begin(), ft_vec_int1.end(), display<int>);
	std::cout << "ft::vector::size = " << ft_vec_int1.size() << std::endl;
	std::cout << "ft::vector::capacity = " << ft_vec_int1.capacity() << std::endl;

	////// VECTOR<STRING> - insert test ///////

	std_vec_string.resize(4);
	ft_vec_string.resize(4);

	std::cout << "<<	std_vec_string" << std::endl;
	std::cout << "std::vector<std::string>::size = " << std_vec_string.size() << std::endl;
	std::cout << "std::vector<std::string>::capacity = " << std_vec_string.capacity() << std::endl;
	std::vector<std::string>::iterator	it_string = std_vec_string.begin();
//	std_vec_string.insert(it_string, 0, 34);
	std::cout << "std_vec_string" << std::endl;
	for_each(std_vec_string.begin(), std_vec_string.end(), display<std::string>);
	std_vec_string.insert(it_string + 1, 17, "e");
	std_vec_string.push_back("me escuchas");
	//std_vec_string.insert(it_string, 2, 2);
	std::cout << "std_vec_string" << std::endl;
	for_each(std_vec_string.begin(), std_vec_string.end(), display<std::string>);
	std::cout << "std::vector<std::string>::size = " << std_vec_string.size() << std::endl;
	std::cout << "std::vector<std::string>::capacity = " << std_vec_string.capacity() << std::endl;


	std::cout << "<<	ft_vec_string" << std::endl;
	std::cout << "ft::vector<std::string>::size = " << ft_vec_string.size() << std::endl;
	std::cout << "ft::vector<std::string>::capacity = " << ft_vec_string.capacity() << std::endl;
	ft::vector<std::string>::iterator	ft_it_string = ft_vec_string.begin();
//	ft_vec_string.insert(ft_it_string, 0, 34);
	std::cout << "ft_vec_string" << std::endl;
	for_each(ft_vec_string.begin(), ft_vec_string.end(), display<std::string>);
	ft_vec_string.insert(ft_it_string + 1, 17, "e");
	ft_vec_string.push_back("me escuchas");
	//std_vec_string.insert(ft_it_string, 2, 2);
	std::cout << "ft_vec_string" << std::endl;
	for_each(ft_vec_string.begin(), ft_vec_string.end(), display<std::string>);
	std::cout << "ft::vector<std::string>::size = " << ft_vec_string.size() << std::endl;
	std::cout << "ft::vector<std::string>::capacity = " << ft_vec_string.capacity() << std::endl;

	std::cout << "reserve funtion:" << std::endl;
	try
	{
		std::cout << "<<	std_vec_string" << std::endl;
		std_vec_string.reserve(80);
		std::cout << "std::vector<std::string>::capacity = " << std_vec_string.capacity() << std::endl;
		for_each(std_vec_string.begin(), std_vec_string.end(), display<std::string>);
		std_vec_string.reserve(std_vec_string.max_size() + 1);
	}
	catch (std::exception &e)
	{
		std::cout << "Lenght error: " << e.what() << std::endl;
	}
	try
	{
		std::cout << "<<	ft_vec_string" << std::endl;
		ft_vec_string.reserve(80);
		std::cout << "ft::vector<std::string>::capacity = " << ft_vec_string.capacity() << std::endl;
		for_each(ft_vec_string.begin(), ft_vec_string.end(), display<std::string>);
		ft_vec_string.reserve(ft_vec_string.max_size() + 1);
	}
	catch (std::exception &e)
	{
		std::cout << "Lenght error: " << e.what() << std::endl;
	}
}
