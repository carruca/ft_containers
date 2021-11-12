#include "ft_pair.hpp"
#include <utility>
#include <string>
#include <iostream>

void	testPair( void )
{
	std::pair<std::string, int>	std_p1;
	std::pair<std::string, int>	std_p2( "tomatoes", 12 );
	std::pair<std::string, int>	std_p3( std_p2 );
	std::pair<std::string, int>	std_p4 = std_p2;

	ft::pair<std::string, int>	ft_p1;
	ft::pair<std::string, int>	ft_p2( "tomatoes", 12 );
	ft::pair<std::string, int>	ft_p3( ft_p2 );
	ft::pair<std::string, int>	ft_p4 = ft_p2;

	std_p1 = std::make_pair( std::string( "oranges" ), 5 );
	ft_p1 = ft::make_pair( std::string( "oranges" ), 5 );

	std::cout << std::endl << "* test: pair: TEST *" << std::endl;
	if ( std_p2 == std_p3 && ft_p2 == ft_p3 )
		std::cout << "constructors:				CHECK!" << std::endl;
	else
		std::cout << "constructors:				WRONG!" << std::endl;

	if ( std_p2 == std_p4 && ft_p2 == ft_p4 )
		std::cout << "operator =:				CHECK!" << std::endl;
	else
		std::cout << "operator =:				WRONG!" << std::endl;

	if ( std_p1 != std_p2 && ft_p1 != ft_p2 )
		std::cout << "operator !=:				CHECK!" << std::endl;
	else
		std::cout << "operator !=:				WRONG!" << std::endl;

	if ( ( std_p1 <= std_p2 ) == ( ft_p1 <= ft_p1 ) )
		std::cout << "operator <=:				CHECK!" << std::endl;
	else
		std::cout << "operator <=:				WRONG!" << std::endl;

	if ( ( std_p1 >= std_p2 ) == ( ft_p1 >= ft_p2 ) )
		std::cout << "operator >=:				CHECK!" << std::endl;
	else
		std::cout << "operator >=:				WRONG!" << std::endl;

	if ( std_p1.first == ft_p1.first )
		std::cout << "make_pair:				CHECK!" << std::endl;
	else
		std::cout << "make_pair:				WRONG!" << std::endl;
}
