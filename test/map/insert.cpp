#include "map.hpp"
#include "struct.hpp"
#include "utils.hpp"

#include <iostream>
#include <sys/time.h>

static unsigned long	get_time( void )
{
	struct timeval	tvp;

	gettimeofday(&tvp, NULL);
	return tvp.tv_sec * 1000 + tvp.tv_usec / 1000;
}

void	map_insert( void )
{
	map_type		map1;
	unsigned long	begin;
	unsigned long	end;
	unsigned long	diff;

	begin = get_time();
	for (size_t i = 0; i < 0xF4240; ++i)
		map1.insert(map_type::value_type(i, "string1"));
	end = get_time();

	diff = end - begin;
	std::cout << "insert map begin duration = " << begin << std::endl;
	std::cout << "insert map end duration = " << end << std::endl;
	std::cout << "insert map time duration = " << diff << std::endl;
}
