#include "global.hpp"
#include "test.hpp"

#include <cstdlib>
#include <iostream>
#include <sys/time.h>

unsigned long	get_time( void )
{
	struct timeval	tvp;

	gettimeofday(&tvp, 0);
	return tvp.tv_sec * 1000 + tvp.tv_usec / 1000;
}

void	check_leaks( void )
{
	system("leaks ft_containers");
}

int	main( void )
{
//	atexit(check_leaks);

	unsigned long	begin(get_time());

//utils

	test_pair();
	test_equal();
	test_lexicographical_compare();
	test_reverse_iterator();

	vector_old_test();

//vector

	vector_default_constructor();
	vector_swap();
	vector_resize();
	vector_assign();
	vector_const_iterators();
	vector_reserve();
	vector_insert();
	vector_swap();

//map

	map_lower_bound();
	map_create_empty();
	map_upper_bound();
	map_equal_range();
	map_size_test();
	map_find_test();
	map_value_comp();
	map_relational_oper();
	map_swap();
	map_insert();
	map_erase();

//stack

	stack_pop();
	stack_size();
	stack_relationals();

	std::cout << "time duration = " << (get_time() - begin) << std::endl;

	return 0;
}
