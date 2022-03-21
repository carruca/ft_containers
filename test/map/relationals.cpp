#include "map.hpp"
#include "struct.hpp"
#include "utils.hpp"

#include <iostream>

map_type	smallest_size = map_type();
map_type	biggest_size = map_type();
map_type	same_size = map_type();

void	map_relational_oper( void )
{
	smallest_size[3] = "smallest one";

	biggest_size[5] = "think i am the greatest";
	biggest_size[67] = "yes, i am the biggest";

	same_size[56] = "same size as biggest al least";
	same_size[34] = "no, probably the greatest is me";

	if (smallest_size != biggest_size)
		std::cout << smallest_size.begin()->second << " is not the same as " << biggest_size.begin()->second << std::endl;

	if (smallest_size < biggest_size)
		std::cout << smallest_size.begin()->second << " is smaller than " << biggest_size.begin()->second << std::endl;

	if (same_size >= biggest_size)
		std::cout << same_size.begin()->second << " is bigger or equal to " << biggest_size.begin()->second << std::endl;

	if (biggest_size <= same_size)
		std::cout << biggest_size.begin()->second << " is smaller or equal to " << same_size.begin()->second << std::endl;
	
//	intMap_iterator	it = smallest_size.begin();
}
