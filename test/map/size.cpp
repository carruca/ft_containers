#include "map.hpp"
#include "struct.hpp"
#include "utils.hpp"

#include <iostream>

map_type	normal_map = map_type();
map_type	unormal_map = map_type(map_type::key_compare(), normal_map.get_allocator());

void	map_size_test( void )
{
	normal_map[1] = "terestegen";
	normal_map[5] = "busquets";
	normal_map[6] = "xavi";
	normal_map[10] = "messi";

	if (unormal_map.empty())
		std::cout << "unormal_map is empty" << std::endl;
	unormal_map[1] = "cesar";
	unormal_map[5] = "puyol";

	std::cout << "normal map size_max = " << normal_map.max_size() << std::endl; 
	std::cout << "normal map lenght = " << normal_map.size() << std::endl;
	std::cout << "unormal map lenght = " << unormal_map.size() << std::endl;

	NAMESPACE::swap<int,std::string>(normal_map, unormal_map);

	normal_map[6] = "xavi";

	std::cout << "normal map lenght = " << normal_map.size() << std::endl;
	std::cout << "unormal map lenght = " << unormal_map.size() << std::endl;

	map_type::size_type	size;

	size = normal_map.count(6);
	if (size)
		std::cout << "node : first = 6 is in normal_map" << std::endl;  
}
