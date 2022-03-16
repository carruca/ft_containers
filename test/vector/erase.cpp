#include "vector.hpp"

#include <iostream>
#include <algorithm>
#include <vector>
#include <stdexcept>
#include <list>

void	display_int(int target);

/*
void	erase_test( void )
{
	typedef std::vector<int>			std_vector_type;
//	typedef ft::vector<int>				ft_vector_type;

//	ft_vector_type		vect_ft(10);
	std_vector_type		vect_std(10);
	
	for (int i = 0; i < 10; ++i)
	{
//		vect_ft[i] = i * 3 + 2;
		vect_std[i] = i * 3 + 2;
	}
	
//	vect_ft.erase(vect_ft.begin() + 2);
	vect_std.erase(vect_std.begin() + 2);

//	for_each(vect_ft.begin(), vect_ft.end(), display_int);
	for_each(vect_std.begin(), vect_std.end(), display_int);
}
*/

void	display_size( size_t size )
{
	std::cout << "size = " << size << std::endl;
}

void	check_erase(ft::vector<std::string> const &vct,
					ft::vector<std::string>::const_iterator const &it)
{
	static int i = 0;
	std::cout << "[" << i++ << "] " << "erase: " << it - vct.begin() << std::endl;
	display_size(vct.size());
}

void	erase_test( void )
{
	std::cout << "<<	Erase test ft vector	>>" << std::endl;

	ft::vector<std::string> vct(10);

	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct[i] = std::string((vct.size() - i), i + 65);
	display_size(vct.size());

	check_erase(vct, vct.erase(vct.begin() + 2));

	check_erase(vct, vct.erase(vct.begin()));
	check_erase(vct, vct.erase(vct.end() - 1));

	check_erase(vct, vct.erase(vct.begin(), vct.begin() + 3));
	check_erase(vct, vct.erase(vct.end() - 3, vct.end() - 1));

	vct.push_back("Hello");
	vct.push_back("Hi there");
	display_size(vct.size());
	check_erase(vct, vct.erase(vct.end() - 3, vct.end()));

	vct.push_back("ONE");
	vct.push_back("TWO");
	vct.push_back("THREE");
	vct.push_back("FOUR");
	display_size(vct.size());
	check_erase(vct, vct.erase(vct.begin(), vct.end()));
}

void	iterator_std_test( void )
{
	std::cout << "<<	Iterator test std vector	>>" << std::endl;	
	const int size = 5;
	std::vector<int> vct(size);
	std::vector<int>::reverse_iterator it = vct.rbegin();
	std::vector<int>::const_reverse_iterator ite = vct.rbegin();

	for (int i = 0; i < size; ++i)
		it[i] = (size - i) * 5;

	it = it + 5;
	it = 1 + it;
	it = it - 4;
	std::cout << *(it += 2) << std::endl;
	std::cout << *(it -= 1) << std::endl;

	*(it -= 2) = 42;
	*(it += 2) = 21;

	std::cout << "const_ite +=/-=: " << *(ite += 2) << " | " << *(ite -= 2) << std::endl;

	std::cout << "(it == const_it): " << (ite == it) << std::endl;
	std::cout << "(const_ite - it): " << (ite - it) << std::endl;
	std::cout << "(ite + 3 == it): " << (ite + 3 == it) << std::endl;

	display_size(vct.size());
}

void	iterator_test( void )
{
	std::cout << "<<	Iterator test ft vector	>>" << std::endl;	

	const int size = 5;
	ft::vector<int> vct(size);
	ft::vector<int>::reverse_iterator it = vct.rbegin();
	ft::vector<int>::const_reverse_iterator ite = vct.rbegin();

	for (int i = 0; i < size; ++i)
		it[i] = (size - i) * 5;

	it = it + 5;
	it = 1 + it;
	it = it - 4;
	std::cout << *(it += 2) << std::endl;
	std::cout << *(it -= 1) << std::endl;

	*(it -= 2) = 42;
	*(it += 2) = 21;

	std::cout << "const_ite +=/-=: " << *(ite += 2) << " | " << *(ite -= 2) << std::endl;

	std::cout << "(it == const_it): " << (ite == it) << std::endl;
	std::cout << "(const_ite - it): " << (ite - it) << std::endl;
	std::cout << "(ite + 3 == it): " << (ite + 3 == it) << std::endl;

	display_size(vct.size());
	iterator_std_test();
}

void	iterator_test2( void )
{
	const int size = 5;
	ft::vector<int> vct(size);
	ft::vector<int>::reverse_iterator it(vct.rbegin());
	ft::vector<int>::const_reverse_iterator ite(vct.rend());

	for (int i = 1; it != ite; ++i)
		*it++ = (i * 7);
	display_size(vct.size());

	it = vct.rbegin();
	ite = vct.rbegin();

	std::cout << *(++ite) << std::endl;
	std::cout << *(ite++) << std::endl;
	std::cout << *ite++ << std::endl;
	std::cout << *++ite << std::endl;

//	it->m();
//	ite->m();

	std::cout << *(++it) << std::endl;
	std::cout << *(it++) << std::endl;
	std::cout << *it++ << std::endl;
	std::cout << *++it << std::endl;

	std::cout << *(--ite) << std::endl;
	std::cout << *(ite--) << std::endl;
	std::cout << *--ite << std::endl;
	std::cout << *ite-- << std::endl;

//	(*it).m();
//	(*ite).m();

	std::cout << *(--it) << std::endl;
	std::cout << *(it--) << std::endl;
	std::cout << *it-- << std::endl;
	std::cout << *--it << std::endl;
}
