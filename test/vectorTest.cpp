#include <iostream>
#include <algorithm>
#include <vector>
#include <stdexcept>
#include <list>
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

	/********* VECTOR<INT> - insert tests **********/

	for_each(std_vec_string.begin(), std_vec_string.end(), display_string);
	for_each(ft_vec_string.begin(), ft_vec_string.end(), display_string);

	std::cout << "<<	std_vec_int1" << std::endl;
	std::cout << "std::vector::size() = " << std_vec_int1.size() << std::endl;
	std::cout << "std::vector::capacity() = " << std_vec_int1.capacity() << std::endl;
	std::vector<int>::iterator	it_int = std_vec_int1.begin();
//	std_vec_int1.insert(it_int, 0, 34);
	std::cout << "std_vec_int" << std::endl;
	for_each(std_vec_int1.begin(), std_vec_int1.end(), display_int);
	std_vec_int1.insert(it_int + 1, 17, 34);
	std_vec_int1.push_back(18);
	//std_vec_int1.insert(it_int, 2, 2);
	std::cout << "std_vec_int" << std::endl;
	for_each(std_vec_int1.begin(), std_vec_int1.end(), display_int);
	std::cout << "std::vector::size() = " << std_vec_int1.size() << std::endl;
	std::cout << "std::vector::capacity() = " << std_vec_int1.capacity() << std::endl;

	std::cout << "<<	ft_vec_int1" << std::endl;
	std::cout << "ft::vector::size() = " << ft_vec_int1.size() << std::endl;
	std::cout << "ft::vector::capacity() = " << ft_vec_int1.capacity() << std::endl;
	ft::vector<int>::iterator	ft_it_int = ft_vec_int1.begin();
//	ft_vec_int1.insert(ft_it_int, 0, 34);
	std::cout << "ft_vec_int" << std::endl;
	for_each(ft_vec_int1.begin(), ft_vec_int1.end(), display_int);
	ft_vec_int1.insert(ft_it_int + 1, 17, 34);
	ft_vec_int1.push_back(18);
	//std_vec_int1.insert(ft_it_int, 2, 2);
	std::cout << "ft_vec_int" << std::endl;
	for_each(ft_vec_int1.begin(), ft_vec_int1.end(), display_int);
	std::cout << "ft::vector::size() = " << ft_vec_int1.size() << std::endl;
	std::cout << "ft::vector::capacity() = " << ft_vec_int1.capacity() << std::endl;

	/********* VECTOR<STRING> - insert test **********/

	std_vec_string.resize(4);
	ft_vec_string.resize(4);

	std::cout << "<<	std_vec_string" << std::endl;
	std::cout << "std::vector<std::string>::size() = " << std_vec_string.size() << std::endl;
	std::cout << "std::vector<std::string>::capacity() = " << std_vec_string.capacity() << std::endl;
	std::vector<std::string>::iterator	it_string = std_vec_string.begin();
//	std_vec_string.insert(it_string, 0, 34);
	std::cout << "std_vec_string" << std::endl;
	for_each(std_vec_string.begin(), std_vec_string.end(), display_string);
	std_vec_string.insert(it_string + 1, 17, "e");
	std_vec_string.push_back("me escuchas");
	//std_vec_string.insert(it_string, 2, 2);
	std::cout << "std_vec_string" << std::endl;
	for_each(std_vec_string.begin(), std_vec_string.end(), display_string);
	std::cout << "std::vector<std::string>::size() = " << std_vec_string.size() << std::endl;
	std::cout << "std::vector<std::string>::capacity() = " << std_vec_string.capacity() << std::endl;


	std::cout << "<<	ft_vec_string" << std::endl;
	std::cout << "ft::vector<std::string>::size() = " << ft_vec_string.size() << std::endl;
	std::cout << "ft::vector<std::string>::capacity() = " << ft_vec_string.capacity() << std::endl;
	ft::vector<std::string>::iterator	ft_it_string = ft_vec_string.begin();
//	ft_vec_string.insert(ft_it_string, 0, 34);
	std::cout << "ft_vec_string" << std::endl;
	for_each(ft_vec_string.begin(), ft_vec_string.end(), display_string);
	ft_vec_string.insert(ft_it_string + 1, 17, "e");
	ft_vec_string.push_back("me escuchas");
	//std_vec_string.insert(ft_it_string, 2, 2);
	std::cout << "ft_vec_string" << std::endl;
	for_each(ft_vec_string.begin(), ft_vec_string.end(), display_string);
	std::cout << "ft::vector<std::string>::size() = " << ft_vec_string.size() << std::endl;
	std::cout << "ft::vector<std::string>::capacity() = " << ft_vec_string.capacity() << std::endl;

	std::cout << "reserve funtion:" << std::endl;
	try
	{
		std::cout << "<<	std_vec_string" << std::endl;
		std_vec_string.reserve(80);
		std::cout << "std::vector<std::string>::capacity() = " << std_vec_string.capacity() << std::endl;
		for_each(std_vec_string.begin(), std_vec_string.end(), display_string);
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
		std::cout << "ft::vector<std::string>::capacity() = " << ft_vec_string.capacity() << std::endl;
		for_each(ft_vec_string.begin(), ft_vec_string.end(), display_string);
		ft_vec_string.reserve(ft_vec_string.max_size() + 1);
	}
	catch (std::exception &e)
	{
		std::cout << "Lenght error: " << e.what() << std::endl;
	}

	std::vector<int>	vct(7);
	std::vector<int>	vct_two(4);
	std::vector<int>	vct_three;
	std::vector<int>	vct_four;

	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct[i] = (vct.size() - i) * 3;
	for (unsigned long int i = 0; i < vct_two.size(); ++i)
		vct_two[i] = (vct_two.size() - i) * 5;
	std::cout << "\t### std::vector<int>::assign(): ###" << std::endl;
	std::cout << "size of std::vector<int> = " << vct.size() << std::endl;
	std::cout << "size of std::vector<int> = " << vct_two.size() << std::endl;

	vct_three.assign(vct.begin(), vct.end());
	vct.assign(vct_two.begin(), vct_two.end());
	vct_two.assign(2, 42);
	vct_four.assign(4, 21);

	std::cout << "\t### After assign(): ###" << std::endl;

	std::cout << "size of std::vector<int> = " << vct.size() << std::endl;
	std::cout << "size of std::vector<int> = " << vct_two.size() << std::endl;
	std::cout << "size of std::vector<int> = " << vct_three.size() << std::endl;
	std::cout << "size of std::vector<int> = " << vct_four.size() << std::endl;

	vct_four.assign(6, 84);
	std::cout << "size of std::vector<int> = " << vct_four.size() << std::endl;

	std::cout << "\t### assign() on enough capacity and low size: ###" << std::endl;

	vct.assign(5, 53);
	vct_two.assign(vct_three.begin(), vct_three.begin() + 3);

	std::cout << "size of std::vector<int> = " << vct.size() << std::endl;
	std::cout << "size of std::vector<int> = " << vct_two.size() << std::endl;

	ft::vector<int>	ft_vct(7);
	ft::vector<int>	ft_vct_two(4);
	ft::vector<int>	ft_vct_three;
	ft::vector<int>	ft_vct_four;

	for (unsigned long int i = 0; i < ft_vct.size(); ++i)
		ft_vct[i] = (ft_vct.size() - i) * 3;
	for (unsigned long int i = 0; i < ft_vct_two.size(); ++i)
		ft_vct_two[i] = (ft_vct_two.size() - i) * 5;
	std::cout << "\t### ft::vector<int>::assign(): ###" << std::endl;
	std::cout << "size of ft::vector<int> = " << ft_vct.size() << std::endl;
	std::cout << "size of ft::vector<int> = " << ft_vct_two.size() << std::endl;

	ft_vct_three.assign(ft_vct.begin(), ft_vct.end());
	ft_vct.assign(ft_vct_two.begin(), ft_vct_two.end());
	ft_vct_two.assign(2, 42);
	ft_vct_four.assign(4, 21);

	std::cout << "\t### After assign(): ###" << std::endl;

	std::cout << "size of ft::vector<int> = " << ft_vct.size() << std::endl;
	std::cout << "size of ft::vector<int> = " << ft_vct_two.size() << std::endl;
	std::cout << "size of ft::vector<int> = " << ft_vct_three.size() << std::endl;
	std::cout << "size of ft::vector<int> = " << ft_vct_four.size() << std::endl;

	ft_vct_four.assign(6, 84);
	std::cout << "size of ft::vector<int> = " << ft_vct_four.size() << std::endl;

	std::cout << "\t### assign() on enough capacity and low size: ###" << std::endl;

	ft_vct.assign(5, 53);
	ft_vct_two.assign(ft_vct_three.begin(), ft_vct_three.begin() + 3);

	std::cout << "size of ft::vector<int> = " << ft_vct.size() << std::endl;
	std::cout << "size of ft::vector<int> = " << ft_vct_two.size() << std::endl;

	std::cout << "\t### bidirection: ###" << std::endl;
	std::list<int>				lst;
	std::list<int>::iterator	lst_it;

	for (int i = 1; i < 5; ++i)
		lst.push_back(i * 3);

	std::vector<int>	vct_bi(lst.begin(), lst.end());
	std::cout << "size of std::vector<int> = " << vct_bi.size() << std::endl;

	lst_it = lst.begin();
	for (int i = 1; lst_it != lst.end(); ++i)
		*lst_it++ = i * 5;
	vct_bi.assign(lst.begin(), lst.end());
	std::cout << "size of std::vector<int> = " << vct_bi.size() << std::endl;

	vct_bi.insert(vct_bi.end(), lst.rbegin(), lst.rend());
	std::cout << "size of std::vector<int> = " << vct_bi.size() << std::endl;

	std::list<int>				lst2;
	std::list<int>::iterator	lst_it2;

	for (int i = 1; i < 5; ++i)
		lst2.push_back(i * 3);

	ft::vector<int>	ft_vct_bi(lst2.begin(), lst2.end());
	std::cout << "size of ft::vector<int> = " << ft_vct_bi.size() << std::endl;

	lst_it2 = lst2.begin();
	for (int i = 1; lst_it2 != lst2.end(); ++i)
		*lst_it2++ = i * 5;
	ft_vct_bi.assign(lst2.begin(), lst2.end());
	std::cout << "size of ft::vector<int> = " << ft_vct_bi.size() << std::endl;

	ft_vct_bi.insert(ft_vct_bi.end(), lst2.rbegin(), lst2.rend());
	std::cout << "size of ft::vector<int> = " << ft_vct_bi.size() << std::endl;

	std::cout << "\t### copy construct: ###" << std::endl;
	ft::vector<int>				ft_vec_int2(5);
	ft::vector<int>::iterator	ft_it_int2 = ft_vec_int2.begin(), ft_it_int2e = ft_vec_int2.end();

	std::cout << "len: " << (ft_it_int2e - ft_it_int2) << std::endl;
	for (; ft_it_int2 != ft_it_int2e; ++ft_it_int2)
		*ft_it_int2 = (ft_it_int2e - ft_it_int2);

	ft_it_int2 = ft_vec_int2.begin();

	ft::vector<int>				ft_vec_int_range(ft_it_int2, --(--ft_it_int2e));

	for (int i = 0; ft_it_int2 != ft_it_int2e; ++ft_it_int2)
		*ft_it_int2 = ++i * 5;

	ft_it_int2 = ft_vec_int2.begin();
	ft::vector<int>				ft_vec_int_copy(ft_vec_int2);
	for (int i = 0; ft_it_int2 != ft_it_int2e; ++ft_it_int2)
		*ft_it_int2 = ++i * 7;
	ft_vec_int_copy.push_back(42);
	ft_vec_int_copy.push_back(21);

	std::cout << "\t-- PART ONE --" << std::endl;
	std::cout << "size of ft::vector<int> = " << ft_vec_int2.size() << std::endl;
	std::cout << "size of ft::vector<int> range = " << ft_vec_int_range.size() << std::endl;
	std::cout << "size of ft::vector<int> copy = " << ft_vec_int_copy.size() << std::endl;

	ft_vec_int2 = ft_vec_int_copy;
	ft_vec_int_copy = ft_vec_int_range;
	ft_vec_int_range.clear();

	std::cout << "\t-- PART TWO --" << std::endl;
	std::cout << "size of ft::vector<int> = " << ft_vec_int2.size() << std::endl;
	std::cout << "size of ft::vector<int> range = " << ft_vec_int_range.size() << std::endl;
	std::cout << "size of ft::vector<int> copy = " << ft_vec_int_copy.size() << std::endl;
}
