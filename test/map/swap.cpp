#include "map.hpp"
#include "struct.hpp"
#include "utils.hpp"

#include <iostream>

map_type	mango_map = map_type();
map_type	orange_map = map_type();
map_type	melon_map = map_type();

void	map_swap( void )
{
/*	for (int i = 0; i < 50; i++)
		melon_map.insert(map_type::value_type(i, "string"));
	std::cout << "melon map created:" << std::endl;
	print_map<int, std::string>(melon_map);

	mango_map[14] = "string0";
	mango_map[89] = "string1";
	mango_map[7] = "string2";
	mango_map[6] = "string3";
	std::cout << "mango map created:" << std::endl;
	print_map<int, std::string>(mango_map);

	orange_map.swap(mango_map);
	std::cout << "orange map swap mango_map:" << std::endl;
	print_map<int, std::string>(orange_map);

	mango_map.swap(melon_map);
	std::cout << "mango map swap melon_map:" << std::endl;
	print_map<int, std::string>(mango_map);
*/
	ft::map<int, std::string> ft_m1, ft_m2;
	for (size_t i = 0; i < 1e6; i++)
	{
		ft_m1.insert(ft::make_pair(i, "string2"));
	}

	ft_m2.swap(ft_m1);
}
