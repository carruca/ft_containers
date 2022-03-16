#include "map.hpp"

#include <map>
#include <string>
#include <iostream>
#include <functional>

# define NAMESPACE	ft

template< typename Key, typename T >
	static void	print_map(NAMESPACE::map<Key, T>& x)
	{
		typedef typename NAMESPACE::map<Key, T>	map_type;

		for (typename map_type::iterator it = x.begin(); it != x.end(); ++it)
		{
			std::cout << "node address = " << &(*it) << std::endl;
			std::cout << "map elem = " << it->first << " : " << it->second << std::endl;
			std::cout << "-----------------------" << std::endl;
		}
		std::cout << "end node map address = " << &(*x.end()) << std::endl;
		std::cout << "         map address = " << &x << std::endl;
		std::cout << "                diff = " << (unsigned long)&(*x.end()) - (unsigned long)&x << std::endl;
	}

void	map_create_empty(void)
{
	typedef NAMESPACE::map<int, int>			intMap_type;

	typedef NAMESPACE::map<int, std::string>	map_type;
	typedef map_type::iterator					map_iterator;

	map_type		play_map;

	play_map.insert(map_type::value_type(12, "Manolo"));
	play_map.insert(map_type::value_type(10, "Figo"));
	play_map.insert(map_type::value_type(7, "Raul"));
	play_map.insert(map_type::value_type(14, "Xabi"));
	play_map.insert(map_type::value_type(1, "Casillas"));

	if ((play_map.insert(map_type::value_type(1, "Courtois"))).second == false)
		std::cout << "cannot insert a unique value key again" << std::endl;

	play_map.insert(play_map.begin(), map_type::value_type(3, "Roberto"));
	play_map.insert(play_map.end(), map_type::value_type(19, "Rodrigo"));

	map_type		play_map2;

	play_map2.insert(play_map.begin(), play_map.end());

	play_map2.insert(play_map2.end(), map_type::value_type(1, "Casillas"));
	play_map2.insert(play_map2.end(), map_type::value_type(3, "Roberto"));
	play_map2.insert(play_map2.end(), map_type::value_type(7, "Raul"));
	play_map2.insert(play_map2.end(), map_type::value_type(10, "Figo"));
	play_map2.insert(play_map2.end(), map_type::value_type(12, "Manolo"));
	play_map2.insert(play_map2.end(), map_type::value_type(14, "Xabi"));
	play_map2.insert(play_map2.end(), map_type::value_type(19, "Rodrigo"));
	play_map2.insert(play_map2.end(), map_type::value_type(20, "Vinicius"));

	play_map[20] = "Vinicius";

	std::cout  << "Best player is = " << play_map[20] << std::endl;

	map_type		play_map3;
	map_iterator	map3_it = play_map3.end();

	play_map3.insert(play_map3.begin(), map_type::value_type(1, "Courtois"));
	play_map3.insert(++play_map3.begin(), map_type::value_type(5, "Puyol"));

	play_map3.insert(map3_it, map_type::value_type(7, "Raul"));
	play_map3.insert(map3_it, map_type::value_type(12, "Manolo"));
	play_map3.insert(map3_it, map_type::value_type(3, "Manolo"));

	--map3_it;
	play_map3.insert(map3_it, map_type::value_type(10, "Robinho"));

	std::cout << "diff between maps = " << (unsigned long)&play_map - (unsigned long)&play_map2 << std::endl;

	std::cout << "PRINT_MAP function" << std::endl;
	std::cout << "play_map 1:" << std::endl;
	print_map<int, std::string>(play_map);
	std::cout << "play_map 2:" << std::endl;
	print_map<int, std::string>(play_map2);
	std::cout << "play_map 3:" << std::endl;
	print_map<int, std::string>(play_map3);
	std::cout << "-----------------------" << std::endl;

	std::cout << "SIZEOF MAP_TYPE" << std::endl;
	std::cout << "size of string = " << sizeof(std::string) << std::endl;
	std::cout << "size of string map = " << sizeof(map_type) << std::endl;
	std::cout << "size of int map = " << sizeof(intMap_type) << std::endl;
}
