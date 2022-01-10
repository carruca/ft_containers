#ifndef SPAN_HPP
# define SPAN_HPP

# include <vector>
# include <algorithm>
# include <iterator>
# include "ft_vector.hpp"

# define NAMESPACE	ft

class	Span
{
public:

	Span( unsigned int N );
	Span( Span const &src );
	~Span( void );

	Span	&operator=( Span const &rhs );

	size_t const			&getSize( void ) const;
	NAMESPACE::vector<int> const	&getContainer( void ) const;

	void	addNumber( int nb );
	void	addNumber( NAMESPACE::vector<int> v );

	unsigned int	shortestSpan( void );
	unsigned int	longestSpan( void );

	class FullSizeException : public std::exception {

	public:

		virtual const char	*what() const throw();
	};

	class SizeTooLowException : public std::exception {

	public:

		virtual const char	*what() const throw();
	};

private:

	size_t					_size;
	NAMESPACE::vector<int>	_vector;

	Span( void );
};

#endif
