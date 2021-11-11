#include "ft_enable_if.hpp"
#include "ft_is_integral.hpp"
#include <type_traits>
#include <iostream>

template< class T >
typename std::enable_if<std::is_integral<T>::value, bool>::type isOdd( T i )
{
	return i % 2;
}

template< class T >
typename ft::enable_if<ft::is_integral<T>::value, bool>::type ft_isOdd( T i )
{
	return i % 2;
}

void	testEnable_if( void )
{
	short int	i = 2;

	std::cout << std::endl << "* test: enable_if: TEST *" << std::endl;
	if ( isOdd( i ) == ft_isOdd( i ) )
		std::cout << "enable_if:				CHECK!" << std::endl;
	else
		std::cout << "enable_if:				WRONG!" << std::endl;
}
