#include "reverse_iterator.hpp"
#include <vector>
#include <map>
#include <iterator>
#include <iostream>

void	test_reverse_iterator( void )
{
	std::vector<int>										intVector;
	std::map<int, int>										intMap;

	typedef std::vector<int>::iterator						iteratorVector_type;
	typedef std::map<int, int>::iterator					iteratorMap_type;
	typedef ft::reverse_iterator<iteratorVector_type>		ft_rev_iteratorVector_type;
	typedef ft::reverse_iterator<iteratorMap_type>		ft_rev_iteratorMap_type;
	typedef std::reverse_iterator<iteratorVector_type>		std_rev_iteratorVector_type;
	typedef std::reverse_iterator<iteratorMap_type>		std_rev_iteratorMap_type;

	for ( int i = 0; i < 10; i++ )
		intVector.push_back(i);
	
	intMap[1] = 12;
	intMap[4] = 3;
	intMap[7] = 34;
	intMap[14] = 2;

	std::cout << std::endl << "* iterators: reverse_iterator TEST *" << std::endl;

	ft_rev_iteratorVector_type	ft_revIt;
	std_rev_iteratorVector_type	std_revIt;

	ft_rev_iteratorVector_type	ft_revFrom(intVector.end());
	ft_rev_iteratorVector_type	ft_revUntil(intVector.begin());

	std_rev_iteratorVector_type	std_revFrom(intVector.end());
	std_rev_iteratorVector_type	std_revUntil(intVector.begin());

	while( ft_revFrom != ft_revUntil || std_revFrom != std_revUntil )
	{
		if ( *ft_revFrom != *std_revFrom )
			std::cout << "constructor:				WRONG!" << std::endl;
		ft_revFrom++;
		std_revFrom++;
		if ( ft_revFrom == ft_revUntil && std_revFrom == std_revFrom )
			std::cout << "constructor:				CHECK!" << std::endl;
	}

	ft_rev_iteratorVector_type	ft_revFrom2(ft_revFrom);
	std_rev_iteratorVector_type	std_revFrom2(std_revFrom);

	if ( *ft_revFrom2.base() == *std_revFrom2.base() )
		std::cout << "base=:					CHECK!" << std::endl;
	else
		std::cout << "base=:					WRONG!" << std::endl;


	ft_revIt = ft_revFrom2;
	std_revIt = std_revFrom2;

	if ( *ft_revIt == *std_revIt )
		std::cout << "operator=:				CHECK!" << std::endl;
	else
		std::cout << "operator=:				WRONG!" << std::endl;

	ft_rev_iteratorVector_type	ft_rev1(intVector.end() + 1);
	std_rev_iteratorVector_type	std_rev1(intVector.end() + 1);

	if ( *ft_rev1 == *std_rev1 )
		std::cout << "dereference:				CHECK!" << std::endl;
	else
		std::cout << "dereference:				WRONG!" << std::endl;

	ft_rev_iteratorMap_type		ft_rev2(intMap.end());
	std_rev_iteratorMap_type	std_rev2(intMap.end());

	if ( ft_rev2->second == std_rev2->second )
		std::cout << "operator->:				CHECK!" << std::endl;
	else
		std::cout << "operator->:				WRONG!" << std::endl;

	ft_rev_iteratorMap_type		ft_rev3(intMap.end());
	std_rev_iteratorMap_type	std_rev3(intMap.end());

	if ( (++ft_rev3)->second == (++std_rev3)->second )
		std::cout << "pre-operator++:				CHECK!" << std::endl;
	else
		std::cout << "pre-operator++:				WRONG!" << std::endl;

	if ( (ft_rev3++)->second == (std_rev3++)->second )
		std::cout << "post-operator++:			CHECK!" << std::endl;
	else
		std::cout << "post-operator++:			WRONG!" << std::endl;
	
	if ( (--ft_rev3)->second == (--std_rev3)->second )
		std::cout << "pre-operator--:				CHECK!" << std::endl;
	else
		std::cout << "pre-operator--:				WRONG!" << std::endl;
	
	if ( (ft_rev3--)->second == (std_rev3--)->second )
		std::cout << "post-operator--:			CHECK!" << std::endl;
	else
		std::cout << "post-operator--:			WRONG!" << std::endl;
	
/*	if ( (ft_rev3 + 1)->second == (std_rev3 + 1)->second )
		std::cout << "operator+:				CHECK!" << std::endl;
	else
		std::cout << "operator+:				WRONG!" << std::endl;
*/

	if ( (ft_rev3 == ft_rev2) == (std_rev3 == std_rev2) )
		std::cout << "operator==:				CHECK!" << std::endl;
	else
		std::cout << "operator==:				WRONG!" << std::endl;
/*	if ( (ft_rev3 <= ft_rev2) == (std_rev3 <= std_rev2) )
		std::cout << "operator<:				CHECK!" << std::endl;
	else
		std::cout << "operator<:				WRONG!" << std::endl;
*/
}
