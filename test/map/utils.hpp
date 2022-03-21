#ifndef MAP_UTILS_HPP
# define MAP_UTILS_HPP

# include "struct.hpp"
# include "map.hpp"

# include <iostream>
# include <map>

template< typename Key, typename T >
	void	print_map(NAMESPACE::map<Key, T>& x)
	{
		typedef typename NAMESPACE::map<Key, T>	map_type;

		for (typename map_type::iterator it = x.begin(); it != x.end(); ++it)
		{
		//	std::cout << "node address = " << &(*it) << std::endl;
			std::cout << "map elem = " << it->first << " : " << it->second << std::endl;
			std::cout << "-----------------------" << std::endl;
		}
	//	std::cout << "end node map address = " << &(*x.end()) << std::endl;
	//	std::cout << "         map address = " << &x << std::endl;
	//	std::cout << "                diff = " << (unsigned long)&(*x.end()) - (unsigned long)&x << std::endl;
	}

#endif
