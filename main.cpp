#include <type_traits>
#include <iostream>

class	A {};

namespace	ft 
{
	template< class T >
	struct	is_integral
	{
		static bool const	value;

	};
};

int	main( void )
{
	std::cout << ft::is_integral<unsigned int>::value << std::endl;
	std::cout << std::is_integral<unsigned int>::value << std::endl;
	return 0;
}
