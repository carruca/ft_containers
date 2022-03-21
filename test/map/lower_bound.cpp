#include "map.hpp"
#include "struct.hpp"
#include "utils.hpp"

#include <map>
#include <string>
#include <iostream>

void	map_lower_bound(void)
{
	map_type	player_map;

	player_map[4] = "dembele";
	player_map[10] = "william";
	player_map[7] = "depay";
	player_map[15] = "guedes";
	player_map[20] = "vinicius";
	
	std::cout << "player_map 1:" << std::endl;
	print_map<int, std::string>(player_map);

	map_iterator	it = player_map.lower_bound(7);
	std::cout << it->first << ":" << it->second << " is the lower_bound of 7" << std::endl;

	it = std::lower_bound(player_map.begin(), player_map.end(), NAMESPACE::pair<const int, std::string>(7, "depay"));
	std::cout << "std::lower_bound of 7 = " << it->first << std::endl;

	map_type	player_map2(player_map.begin(), player_map.end());
	std::cout << "player_map 2:" << std::endl;
	print_map<int, std::string>(player_map);

	map_const_iterator	const_it;

	const_it = player_map2.lower_bound(10);
	std::cout << const_it->first << ":" << const_it->second << " is the lower_bound of 10" << std::endl;
}
