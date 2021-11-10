#ifndef PAIR_HPP
# define PAIR_HPP

namespace	ft
{
	template< class T1, class T2 >
	struct	pair
	{
		typedef T1	first_type;
		typedef T2	second_type;

		T1	first;
		T2	second;

		pair( void ) : first(), second()
		{};

		pair( const T1& x, const T2& y ) : first( x ), second( y )
		{};

		template< class U1, class U2 >
		pair( const pair<U1, U2>& p) : first( p.first ), second( p.second )
		{};

//		pair( const pair& p );
	};
};

#endif
