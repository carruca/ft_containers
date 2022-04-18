#include "map.hpp"
#include "struct.hpp"
#include "utils.hpp"

#include <iostream>

void	map_count( void )
{
	map_type	m1;

	m1[1] = "hola";
	m1[2] = "adios";
	m1[3] = "hasta";
	m1[4] = "nunca";
	m1[5] = "luego";
	m1[6] = "siempre";
	m1[7] = "bye";

	std::cout << "size map 1 = " << m1.size() << std::endl;

	for (int i = 1; i < 9; ++i)
	{
		std::cout << "element " << i << (m1.count(i) ? " DOES" : " DOES NOT") << " exist in map after count" << std::endl;
	}
	m1.clear();
	std::cout << "element 1 " << (m1.count(1) ? " DOES" : " DOES NOT") << " exist in map after count" << std::endl;
	std::cout << "size map 1 = " << m1.size() << std::endl;

}
