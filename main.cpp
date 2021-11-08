#include <type_traits>
#include <iostream>
#include <type_traits>

class	A {};

namespace	ft 
{
	template< class T >
	struct	is_integral
	{
		static bool const	value = false;
	};

	template<>
	struct	is_integral<bool>
	{
		static bool const	value = true;
	};

	template<>
	struct	is_integral<char>
	{
		static bool const	value = true;
	};

	template<>
	struct	is_integral<char16_t>
	{
		static bool const	value = true;
	};

	template<>
	struct	is_integral<char32_t>
	{
		static bool const	value = true;
	};

	template<>
	struct	is_integral<wchar_t>
	{
		static bool const	value = true;
	};

	template<>
	struct	is_integral<signed char>
	{
		static bool const	value = true;
	};

	template<>
	struct	is_integral<short int>
	{
		static bool const	value = true;
	};

	template<>
	struct	is_integral<int>
	{
		static bool const	value = true;
	};

	template<>
	struct	is_integral<long int>
	{
		static bool const	value = true;
	};

	template<>
	struct	is_integral<long long int>
	{
		static bool const	value = true;
	};

	template<>
	struct	is_integral<unsigned char>
	{
		static bool const	value = true;
	};

	template<>
	struct	is_integral<unsigned short int>
	{
		static bool const	value = true;
	};

	template<>
	struct	is_integral<unsigned int>
	{
		static bool const	value = true;
	};

	template<>
	struct	is_integral<unsigned long int>
	{
		static bool const	value = true;
	};

	template<>
	struct	is_integral<unsigned long long int>
	{
		static bool const	value = true;
	};
};

int	main( void )
{
	std::cout << std::boolalpha;
	std::cout << "unsigned int: " << ft::is_integral<unsigned int>::value << std::endl;
	std::cout << "unsigned int: " << std::is_integral<unsigned int>::value << std::endl;

	std::cout << "float: " << std::is_integral<float>::value << std::endl;
	std::cout << "float: " << ft::is_integral<float>::value << std::endl;

	return 0;
}
