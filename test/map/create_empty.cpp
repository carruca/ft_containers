#include <map>
#include <string>
#include <iostream>
#include <functional>
#include "ft_map.hpp"
#include "ft_tree.hpp"

# define NAMESPACE	ft

template< typename Key, typename T >
	static void	print_map(NAMESPACE::map<Key, T>& x)
	{
		typedef typename NAMESPACE::map<Key, T>	map_type;

		for (typename map_type::iterator it = x.begin(); it != x.end(); ++it)
		{
			std::cout << "node address = " << &(*it) << std::endl;
			std::cout << "map elem = " << it->first << " : " << it->second << std::endl;
		}
		std::cout << "end node map address = " << &(*x.end()) << std::endl;
		std::cout << "         map address = " << &x << std::endl;
		std::cout << "                diff = " << (unsigned long)&(*x.end()) - (unsigned long)&x << std::endl;
	}

void	map_create_empty(void)
{
	typedef NAMESPACE::map<int, std::string>	map_type;
	typedef NAMESPACE::map<int, int>		intMap_type;

	map_type		player_map;
	map_type		player_map2;

	player_map.insert(NAMESPACE::pair<int, std::string>(12, "Manolo"));
	player_map.insert(NAMESPACE::pair<int, std::string>(3, "Figo"));
	player_map.insert(NAMESPACE::pair<int, std::string>(7, "Raul"));
	player_map.insert(NAMESPACE::pair<int, std::string>(14, "Xabi"));
	player_map.insert(NAMESPACE::pair<int, std::string>(1, "Casillas"));
//	player_map[3] = "Figo";

	std::cout << "PRINT_MAP function" << std::endl;
	std::cout << "begin=" << player_map.begin()->first << std::endl;
	std::cout << "end=" << player_map2.end()->first << std::endl;
	print_map<int, std::string>(player_map);
//	print_map<int, std::string>(player_map2);
	std::cout << "size of std::string " << sizeof(std::string) << std::endl;
	std::cout << "size of map " << sizeof(map_type) << std::endl;
	std::cout << "size of int map " << sizeof(intMap_type) << std::endl;
	std::cout << "diff between maps = " << (unsigned long)&player_map - (unsigned long)&player_map2 << std::endl;
}
