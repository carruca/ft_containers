#include "map.hpp"
#include "struct.hpp"
#include "utils.hpp"

#include <iostream>

intMap_type	naive_map = intMap_type();
intMap_type	odd_map = intMap_type(naive_map.key_comp(), naive_map.get_allocator());

void	map_find_test( void )
{
	odd_map[14] = 12;
	odd_map[89] = 1;
	odd_map[7] = 4;
	odd_map[6] = 56;

	naive_map = odd_map;

	print_map<int, int>(naive_map);

	intMap_iterator	pos;

	pos = naive_map.find(5);
	if (pos == naive_map.end())
		std::cout << "number 5 not found in naive_map" << std::endl;
	
	pos = odd_map.find(89);
	if (pos != odd_map.end())
		std::cout << "number 5 is found in odd_map : first = " << pos->first << " : second = " << pos->second << std::endl;
	intMap_type const	promo_map(naive_map.begin(), naive_map.end());
	intMap_const_iterator	const_pos(promo_map.find(14));

	if (const_pos != promo_map.end())
		std::cout << "numer " << const_pos->first << " : second " << const_pos->second << " is found" << std::endl;
}
