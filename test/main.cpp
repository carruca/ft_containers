#include <cstdlib>
#include <iostream>
#include <sys/time.h>

void	testIs_integral( void );
void	testEnable_if( void );
void	testPair( void );
void	testEqual( void );
void	testLexicographical_compare( void );
void	testReverseIterator( void );
void	testVector( void );

void	map_lower_bound( void );
void	map_upper_bound( void );
void	map_create_empty( void );
void	map_equal_range( void );
void	map_size_test( void );
void	map_find_test( void );
void	map_value_comp( void );
void	map_relational_oper( void );
void	map_swap( void );
void	map_insert( void );
void	map_erase( void );

void	pop_stack_test( void );

void	check_leaks( void )
{
	system("leaks ft_containers");
}

unsigned long	get_time( void )
{
	struct timeval	tvp;

	gettimeofday(&tvp, NULL);
	return tvp.tv_sec * 1000 + tvp.tv_usec / 1000;
}

int	main( void )
{

	unsigned long	begin;
	unsigned long	end;
	unsigned long	diff;

	begin = get_time();
//vector
	testVector();
//	atexit(check_leaks);
//	testIs_integral();
//	testEnable_if();
//	testPair();
//	testEqual();
//	testLexicographical_compare();
//	testReverseIterator();

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
	pop_stack_test();
	end = get_time();

	diff = end - begin;
/*	std::cout << "begin duration = " << begin << std::endl;
	std::cout << "end duration = " << end << std::endl;
*/	std::cout << "time duration = " << diff << std::endl;

	return 0;
}
