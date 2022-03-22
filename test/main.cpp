#include <cstdlib>

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

void	pop_stack_test( void );

void	check_leaks( void )
{
	system("leaks ft_containers");
}

int	main( void )
{
//vector
//	testVector();
//	atexit(check_leaks);
//	testIs_integral();
//	testEnable_if();
//	testPair();
//	testEqual();
//	testLexicographical_compare();
//	testReverseIterator();

//map
//	map_lower_bound();
//	map_create_empty();
//	map_upper_bound();
//	map_equal_range();
//	map_size_test();
//	map_find_test();
//	map_value_comp();
//	map_relational_oper();
	map_swap();

//stack
//	pop_stack_test();
	return 0;
}
