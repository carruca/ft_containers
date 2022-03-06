#include <map>
#include <string>
#include <iostream>

# define NAMESPACE	std

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
	typedef map_type::iterator					iterator;

	map_type	player_map;

	player_map[4] = "dembele";
	player_map[10] = "william";
	player_map[7] = "depay";
	player_map[15] = "guedes";
	player_map[20] = "vinicius";
	
	print_map<int, std::string>(player_map);

	iterator	it = player_map.upper_bound(7);
	std::cout << it->first << ":" << it->second << " is the upper_bound of 7" << std::endl;

//	it = std::upper_bound(player_map.begin(), player_map.end(), std::pair<const int, std::string>(7, "depay"));
	std::cout << "std::upper_bound of 7 = " << it->first << std::endl;
}
