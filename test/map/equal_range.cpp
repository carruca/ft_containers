#include "map.hpp"
#include "struct.hpp"
#include "utils.hpp"

#include <iostream>

map_type	default_map = map_type();

void	map_equal_range( void )
{
	default_map[4] = "alaba";
	default_map[10] = "rodrigo";
	default_map[7] = "mbappe";
	default_map[15] = "valverde";
	default_map[20] = "vinicius";

	map_type	player_map;
	pair_type	pair_range;

	player_map.insert(default_map.begin(), default_map.end());

	pair_range = player_map.equal_range(3);
	std::cout << pair_range.first->first << ":" << pair_range.first->second << " is the equal range of 3" << std::endl;

	pair_const_type	pair_const_range;

	pair_const_range = player_map.equal_range(15);
	std::cout << pair_const_range.first->first << ":" << pair_const_range.first->second << " is the equal range of 15" << std::endl;
}
