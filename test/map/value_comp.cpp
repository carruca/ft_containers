#include "map.hpp"
#include "struct.hpp"
#include "utils.hpp"

#include <iostream>

intMap_type	foo_map = intMap_type();
intMap_type	bar_map = intMap_type(foo_map.key_comp());

void	map_value_comp( void )
{
	bar_map[4] = 34;
	bar_map[3] = 54;
	bar_map[1] = 78;
	bar_map[6] = 40;
	bar_map[0] = 45;

	intMap_iterator	begin = bar_map.begin();
	intMap_iterator	last = --bar_map.end();

	bool ret;

	ret = foo_map.value_comp()(*begin, *last);
	if (ret)
		std::cout << "node : first = " << begin->first << " : second = " << begin->second << " is smaller" << std::endl;

	intMap_const_iterator	mid = ++bar_map.begin();
	intMap_const_iterator	west = --last;

	ret = foo_map.value_comp()(*west, *mid);
	if (!ret)
		std::cout << "node : first = " << mid->first << " : second = " << mid->second << " is smaller" << std::endl;

	intMap_type::key_compare	comp(foo_map.key_comp());

	std::cout << "the first is " << (comp(bar_map.begin()->first, (++bar_map.begin())->first) ? "" : "NOT") << " the smallest one" << std::endl;
}
