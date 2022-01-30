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

void	check_leaks( void )
{
	system("leaks ft_containers");
}

int	main( void )
{
//	atexit(check_leaks);
	testIs_integral();
	testEnable_if();
	testPair();
	testEqual();
	testLexicographical_compare();
//	testReverseIterator();
	testVector();


	map_lower_bound();
	map_upper_bound();
	return 0;
}
