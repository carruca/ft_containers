#include "ft_map.hpp"

#include <map>
#include <string>
#include <iostream>

# define NAMESPACE	ft

template< typename Key, typename T >
	static void	print_map(NAMESPACE::map<Key, T>& x)
	{
		typedef typename NAMESPACE::map<Key, T>	map_type;

		for (typename map_type::iterator it = x.begin(); it != x.end(); ++it)
			std::cout << "map elem = " << it->first << " : " << it->second << std::endl;
	}

void	map_upper_bound(void)
{
	typedef NAMESPACE::map<int, std::string>	map_type;
	typedef map_type::iterator					map_iterator;

	map_type	player_map;

	player_map[4] = "dembele";
	player_map[10] = "william";
	player_map[7] = "depay";
	player_map[15] = "guedes";
	player_map[20] = "vinicius";

	print_map<int, std::string>(player_map);

	map_iterator	pos = player_map.upper_bound(7);
	std::cout << pos->first << ":" << pos->second << " is the upper_bound of 7" << std::endl;

	map_type	player_map2(player_map);

	std::cout << "copy constructor called" << std::endl;
	print_map<int, std::string>(player_map2);

	map_type	player_map3 = player_map;

	std::cout << "assign operator called" << std::endl;
	print_map<int, std::string>(player_map2);

	map_type	player_map4;

	player_map4.insert(map_type::value_type(4, "dembele"));
	player_map4.insert(map_type::value_type(1, "casillas"));
	std::cout << "player_map 4:" << std::endl;
	print_map<int, std::string>(player_map4);

	map_type	player_map5(player_map4);

	std::cout << "player_map 5:" << std::endl;
	print_map<int, std::string>(player_map5);

	map_type::allocator_type	alloc(player_map.get_allocator());
	std::cout << "allocator = " << &alloc  << std::endl;
	alloc = player_map3.get_allocator();
	std::cout << "assign allocator = " << &alloc << std::endl;

//	it = std::upper_bound(player_map.begin(), player_map.end(), std::pair<const int, std::string>(7, "depay"));
//	std::cout << "std::upper_bound of 7 = " << it->first << std::endl;
}
