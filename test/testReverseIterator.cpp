#include "ft_reverse_iterator.hpp"
#include <vector>
#include <iterator>
#include <iostream>

void	testReverseIterator( void )
{
	std::vector<int>								intVector;

	typedef std::vector<int>::iterator				iterator_type;
	typedef ft::reverse_iterator<iterator_type>		ft_rev_iterator_type;
	typedef std::reverse_iterator<iterator_type>	std_rev_iterator_type;

	for ( int i = 0; i < 10; i++ )
		intVector.push_back(i);

	std::cout << std::endl << "* iterators: reverse_iterator TEST *" << std::endl;

	ft_rev_iterator_type	ft_revIt;
	std_rev_iterator_type	std_revIt;

	ft_rev_iterator_type	ft_revFrom(intVector.end());
	ft_rev_iterator_type	ft_revUntil(intVector.begin());

	std_rev_iterator_type	std_revFrom(intVector.end());
	std_rev_iterator_type	std_revUntil(intVector.begin());

	while( ft_revFrom != ft_revUntil || std_revFrom != std_revUntil )
	{
		if ( *ft_revFrom != *std_revFrom )
			std::cout << "constructor:				WRONG!" << std::endl;
		ft_revFrom++;
		std_revFrom++;
		if ( ft_revFrom == ft_revUntil && std_revFrom == std_revFrom )
			std::cout << "constructor:				CHECK!" << std::endl;
	}

	ft_rev_iterator_type	ft_revFrom2(intVector.end());
	std_rev_iterator_type	std_revFrom2(intVector.end());

	ft_revIt = ft_revFrom2;
	std_revIt = std_revFrom2;

	if ( *ft_revIt == *std_revIt )
		std::cout << "operator=:				CHECK!" << std::endl;
	else
		std::cout << "operator=:				WRONG!" << std::endl;
		
}
