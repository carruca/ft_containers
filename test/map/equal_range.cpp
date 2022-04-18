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

	map_type	player_map(default_map);

	pair_type	pair_range;

	pair_range = player_map.equal_range(3);
	std::cout << pair_range.first->first << ":" << pair_range.first->second << " is the equal range of 3" << std::endl;

	pair_const_type	pair_const_range;

	pair_const_range = player_map.equal_range(15);
	std::cout << pair_const_range.first->first << ":" << pair_const_range.first->second << " is the equal range of 15" << std::endl;

	map_type	player_map2;

	player_map2[34] = "gabriel";
	player_map2[1] = "valdes";
	player_map2[12] = "cazorla";
	player_map2[10] = "messi";
	player_map2[6] = "xavi";

	player_map = player_map2;

	pair_type	pair_range2(player_map.equal_range(1));

	std::cout << pair_range2.first->first << ":" << pair_range2.first->second << " is the equal range of 1" << std::endl;
}
