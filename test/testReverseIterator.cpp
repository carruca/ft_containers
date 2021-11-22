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

	iterator_type									from(intVector.begin());
	iterator_type									until(intVector.end());
	ft_rev_iterator_type							ft_revIt;
	ft_rev_iterator_type							ft_revFrom(until);
	ft_rev_iterator_type							ft_revUntil(from);
	std_rev_iterator_type							std_revIt;
	std_rev_iterator_type							std_revFrom(until);
	std_rev_iterator_type							std_revUntil(from);

	for ( int i = 0; i < 10; i++ )
		intVector.push_back(i);

	std::cout << std::endl << "* iterators: reverse_iterator TEST *" << std::endl;
	while( ft_revFrom != ft_revUntil || std_revFrom != std_revUntil )
	{
		if ( *ft_revFrom != *std_revFrom )
			std::cout << "explicit constructor:				WRONG!" << std::endl;
		ft_revFrom++;
		std_revFrom++;
	}
	std::cout << "explicit constructor:				CHECK!" << std::endl;

//	std::cout << "until = " << *intVector.begin() << std::endl;
	ft_rev_iterator_type	ft_revUntil2(intVector.begin());
	std_rev_iterator_type	std_revUntil2(intVector.begin());
	ft_revIt = ft_revUntil2;
	std_revIt = std_revUntil2;
	std::cout << *std_revUntil2 << std::endl;
//	if ( *ft_revIt == *std_revIt )
		std::cout << "operator=:				CHECK!" << std::endl;
//	else
		std::cout << "operator=:				WRONG!" << std::endl;
		
}
