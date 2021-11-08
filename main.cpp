#include "is_integral.hpp"
#include <type_traits>
#include <iostream>
#include <type_traits>

class	A {};

void	testIsIntegral( void )
{
	std::cout << std::boolalpha;

	std::cout << "std -bool:		" << ft::is_integral<unsigned int>::value << std::endl;
	std::cout << "ft  -bool:		" << std::is_integral<unsigned int>::value << std::endl;

	std::cout << "std -char:		" << ft::is_integral<char>::value << std::endl;
	std::cout << "ft  -char:		" << std::is_integral<char>::value << std::endl;

	std::cout << "std -unsigned int:	" << ft::is_integral<unsigned int>::value << std::endl;
	std::cout << "ft  -unsigned int:	" << std::is_integral<unsigned int>::value << std::endl;

	std::cout << "std -long long int:	" << ft::is_integral<long long int>::value << std::endl;
	std::cout << "ft  -long long int:	" << std::is_integral<long long int>::value << std::endl;

	std::cout << "std -float:		" << std::is_integral<float>::value << std::endl;
	std::cout << "ft  -float:		" << ft::is_integral<float>::value << std::endl;

	std::cout << "std -class A:		" << std::is_integral<A>::value << std::endl;
	std::cout << "ft  -class A:		" << ft::is_integral<A>::value << std::endl;

	return ;
}

int	main( void )
{
	testIsIntegral();
	return 0;
}
