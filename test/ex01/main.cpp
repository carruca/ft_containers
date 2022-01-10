#include "Span.hpp"
#include <iostream>

int	main( void ) {

	Span	sp1 = Span( 5 );

	try {

		sp1.addNumber( 5 );
		sp1.addNumber( 3 );
		sp1.addNumber( 17 );
		sp1.addNumber( 9 );
		sp1.addNumber( 11 );

		std::cout << "Shortest is " << sp1.shortestSpan() << std::endl;
		std::cout << "Longest is " << sp1.longestSpan() << std::endl;
	}
	catch ( std::exception &e ) {

		std::cout << "Sorry, " << e.what() << std::endl;
	}

	std::cout << std::endl;

	Span					sp2 = Span( 1000 );
	NAMESPACE::vector<int>	v1;

	try {

		for ( int i = 0; i < 1000; i++ )
			v1.push_back( i );
		sp2.addNumber( v1 );

		std::cout << "Shortest is " << sp2.shortestSpan() << std::endl;
		std::cout << "Longest is " << sp2.longestSpan() << std::endl;
	}
	catch ( std::exception &e ) {

		std::cout << "Sorry, " << e.what() << std::endl;
	}

	std::cout << std::endl;

	Span			sp3( 1 );

	try {

		sp3.addNumber( 5 );
		sp3.addNumber( 2 );
	}
	catch ( std::exception &e ) {

		std::cout << "Sorry, " << e.what() << std::endl;
	}

	std::cout << std::endl;

	Span			sp4( 1 );
	unsigned int	shortest;
	unsigned int	longest;

	try {

		sp4.addNumber( 5 );

		shortest = sp4.shortestSpan();
		longest = sp4.longestSpan();
		std::cout << "Shortest is " << shortest << std::endl;
		std::cout << "Longest is " <<  longest << std::endl;
	}
	catch ( std::exception &e ) {

		std::cout << "Sorry, " << e.what() << std::endl;
	}

	std::cout << std::endl;

	Span		sp5( sp1 );

	try {

		std::cout << "Shortest is " << sp5.shortestSpan() << std::endl;
		std::cout << "Longest is " << sp5.longestSpan() << std::endl;
	}
	catch ( std::exception &e ) {

		std::cout << "Sorry, " << e.what() << std::endl;
	}

	return 0;
}
