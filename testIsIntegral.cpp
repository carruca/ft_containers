#include "is_integral.hpp"
#include <type_traits>
#include <iostream>

class	A {};

void	testIsIntegral( void )
{
	std::cout << std::endl << "* utils: is_integral TEST: *" << std::endl; 

	if ( ft::is_integral<bool>::value == std::is_integral<bool>::value )
		std::cout << "is_integral<bool>:			CHECK!" << std::endl;
	else
		std::cout << "is_integral<bool>:			WRONG!" << std::endl;

	if ( ft::is_integral<char>::value == std::is_integral<char>::value )
		std::cout << "is_integral<char>:			CHECK!" << std::endl;
	else
		std::cout << "is_integral<char>:			WRONG!" << std::endl;

	if ( ft::is_integral<wchar_t>::value == std::is_integral<wchar_t>::value )
		std::cout << "is_integral<wchar_t>:			CHECK!" << std::endl;
	else
		std::cout << "is_integral<wchar_t>:			WRONG!" << std::endl;

	if ( ft::is_integral<signed char>::value == std::is_integral<signed char>::value )
		std::cout << "is_integral<signed char>:		CHECK!" << std::endl;
	else
		std::cout << "is_integral<signed char>:		WRONG!" << std::endl;

	if ( ft::is_integral<short int>::value == std::is_integral<short int>::value )
		std::cout << "is_integral<short int>:			CHECK!" << std::endl;
	else
		std::cout << "is_integral<short int>:			WRONG!" << std::endl;

	if ( ft::is_integral<int>::value == std::is_integral<int>::value )
		std::cout << "is_integral<int>:			CHECK!" << std::endl;
	else
		std::cout << "is_integral<int>:			WRONG!" << std::endl;

	if ( ft::is_integral<long int>::value == std::is_integral<long int>::value )
		std::cout << "is_integral<long int>:			CHECK!" << std::endl;
	else
		std::cout << "is_integral<long int>:			WRONG!" << std::endl;

	if ( ft::is_integral<long long int>::value == std::is_integral<long long int>::value )
		std::cout << "is_integral<long long int>:		CHECK!" << std::endl;
	else
		std::cout << "is_integral<long long int>:		WRONG!" << std::endl;

	if ( ft::is_integral<unsigned char>::value == std::is_integral<unsigned char>::value )
		std::cout << "is_integral<unsigned char>:		CHECK!" << std::endl;
	else
		std::cout << "is_integral<unsigned char>:		WRONG!" << std::endl;

	if ( ft::is_integral<unsigned short int>::value == std::is_integral<unsigned short int>::value )
		std::cout << "is_integral<unsigned short int>:	CHECK!" << std::endl;
	else
		std::cout << "is_integral<unsigned short int>:	WRONG!" << std::endl;

	if ( ft::is_integral<unsigned int>::value == std::is_integral<unsigned int>::value )
		std::cout << "is_integral<unsigned int>:		CHECK!" << std::endl;
	else
		std::cout << "is_integral<unsigned int>:		WRONG!" << std::endl;

	if ( ft::is_integral<unsigned long int>::value == std::is_integral<unsigned long int>::value )
		std::cout << "is_integral<unsigned long int>:		CHECK!" << std::endl;
	else
		std::cout << "is_integral<unsigned long int>:		WRONG!" << std::endl;

	if ( ft::is_integral<unsigned long long int>::value == std::is_integral<unsigned long long int>::value )
		std::cout << "is_integral<unsigned long long int>:	CHECK!" << std::endl;
	else
		std::cout << "is_integral<unsigned long long int>:	WRONG!" << std::endl;

	if ( ft::is_integral<float>::value == std::is_integral<float>::value )
		std::cout << "is_integral<float>:			CHECK!" << std::endl;
	else
		std::cout << "is_integral<float>:			WRONG!" << std::endl;

	if ( ft::is_integral<A>::value == std::is_integral<A>::value )
		std::cout << "is_integral<A>:				CHECK!" << std::endl;
	else
		std::cout << "is_integral<A>:				WRONG!" << std::endl;

	return ;
}
