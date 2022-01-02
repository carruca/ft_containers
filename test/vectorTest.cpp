#include <iostream>
#include <algorithm>
#include <vector>
#include <stdexcept>
#include "ft_vector.hpp"

void	display_int( int target ) {

	std::cout << "elem = " << target << std::endl;
	return ;
}

void	display_string( std::string target ) {

	std::cout << "elem = " << target << std::endl;
	return ;
}

class	A
{
public:
	A(void)
	{
		std::cout << "A constructor called" << std::endl;
	}
	~A(void)
	{
		std::cout << "A destructor called" << std::endl;
	}
};

void	testVector(void)
{
	std::vector<int>	std_vec_int1;
	ft::vector<int>		ft_vec_int1;
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
//	std_vec_int1.push_back(7);
	std_vec_int1.push_back(989);
	std_vec_int1.push_back(7);

	std::cout << "std::vector::capacity() = " << std_vec_int1.capacity() << std::endl;
	ft_vec_int1.push_back(1);
	ft_vec_int1.push_back(7);
//	ft_vec_int1.push_back(12);
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
/*	try
	{
		ft_vec_int1.resize(ft_vec_int1.max_size() + 1);
	}
	catch ( std::exception& e )
	{
		std::cout << "Length error: " << e.what() << std::endl;
	}
*/
	for_each(std_vec_int1.begin(), std_vec_int1.end(), display_int);
	for_each(ft_vec_int1.begin(), ft_vec_int1.end(), display_int);
	std_vec_int1.resize(2);
	ft_vec_int1.resize(2);
	std::cout << "std::vector::capacity() = " << std_vec_int1.capacity() << std::endl;
	std::cout << "ft::vector::capacity() = " << ft_vec_int1.capacity() << std::endl;
	for_each(std_vec_int1.begin(), std_vec_int1.end(), display_int);
	for_each(ft_vec_int1.begin(), ft_vec_int1.end(), display_int);
	//std_vA.push_back(a1);
	//ft_vA.push_back(a1);
//	std_vA.push_back(a2);
	std::vector<int>	std_v2 = std_vec_int1;
	ft::vector<int>		ft_v2 = ft_vec_int1;

	std::cout << "assignment operator:" << std::endl;
	for_each(std_v2.begin(), std_v2.end(), display_int);
	for_each(ft_v2.begin(), ft_v2.end(), display_int);
	std::cout << "std::vector::capacity() = " << std_v2.capacity() << std::endl;
	std::cout << "ft::vector::capacity() = " << ft_v2.capacity() << std::endl;

	std::vector<std::string>	std_vec_string;
	ft::vector<std::string>		ft_vec_string;

	std_vec_string.push_back("hola");
	std_vec_string.push_back("que");
	std_vec_string.push_back("tal");

	ft_vec_string.push_back("hola");
	ft_vec_string.push_back("que");
	ft_vec_string.push_back("tal");

	for_each(std_vec_string.begin(), std_vec_string.end(), display_string);
	for_each(ft_vec_string.begin(), ft_vec_string.end(), display_string);

	std::cout << "<<	std_vec_int1" << std::endl;
	std::vector<int>::iterator	it_int = std_vec_int1.begin();
//	std_vec_int1.insert(it_int, 0, 34);
	std::cout << "std_vec_int" << std::endl;
	for_each(std_vec_int1.begin(), std_vec_int1.end(), display_int);
	std_vec_int1.insert(it_int + 1, 3, 34);
	//std_vec_int1.insert(it_int, 2, 2);
	std::cout << "std_vec_int" << std::endl;
	for_each(std_vec_int1.begin(), std_vec_int1.end(), display_int);
	std::cout << "std::vector::size() = " << std_vec_int1.size() << std::endl;
	std::cout << "std::vector::capacity() = " << std_vec_int1.capacity() << std::endl;

	std::cout << "<<	ft_vec_int1" << std::endl;
	ft::vector<int>::iterator	ft_it_int = ft_vec_int1.begin();
//	ft_vec_int1.insert(ft_it_int, 0, 34);
	std::cout << "ft_vec_int" << std::endl;
	for_each(ft_vec_int1.begin(), ft_vec_int1.end(), display_int);
	ft_vec_int1.insert(ft_it_int + 1, 3, 34);
	//std_vec_int1.insert(ft_it_int, 2, 2);
	std::cout << "ft_vec_int" << std::endl;
	for_each(ft_vec_int1.begin(), ft_vec_int1.end(), display_int);
	std::cout << "ft::vector::size() = " << ft_vec_int1.size() << std::endl;
	std::cout << "ft::vector::capacity() = " << ft_vec_int1.capacity() << std::endl;
}
