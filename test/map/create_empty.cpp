#include <map>
#include <string>
#include <iostream>
#include <functional>
#include "ft_map.hpp"
#include "ft_tree.hpp"

# define NAMESPACE	ft

template< typename Key, typename T >
	void	print_map(NAMESPACE::map<Key, T>& x)
	{
		typedef typename NAMESPACE::map<Key, T>	map_type;

		for (typename map_type::iterator it = x.begin(); it != x.end(); ++it)
			std::cout << "map elem = " << it->first << " : " << it->second << std::endl;
	}

void	map_create_empty(void)
{
	typedef NAMESPACE::map<int, std::string>	map_type;

	map_type	player_map;

	player_map.insert(NAMESPACE::pair<int, std::string>(12, "Manolo"));
	player_map.insert(NAMESPACE::pair<int, std::string>(3, "Figo"));
//	player_map[3] = "Figo";

//	print_map<int, std::string>(player_map);
}
