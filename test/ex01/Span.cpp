#include "Span.hpp"
#include <iostream>

Span::Span( unsigned int N )
: _size( N )
{
	return ;
}

Span::Span( Span const &src )
: _size( src.getSize() )
, _vector( src.getContainer() )
{
	*this = src;
	return ;
}

Span::~Span( void )
{
	return ;
}

Span	&Span::operator=( Span const &rhs )
{
	if ( this == &rhs )
	{
		this->_size = rhs.getSize();
		this->_vector = rhs.getContainer();
	}	
	return *this;
}

size_t const	&Span::getSize( void ) const
{
	return this->_size;
}

NAMESPACE::vector<int> const	&Span::getContainer( void ) const
{
	return this->_vector;
}

void	Span::addNumber( int nb )
{
	if ( this->_size == this->_vector.size() )
		throw FullSizeException();
	this->_vector.push_back( nb );
	return ;
}

void	Span::addNumber( NAMESPACE::vector<int> v )
{
	if ( this->_size < this->_vector.size() + v.size())
		throw FullSizeException();
	this->_vector.insert( this->_vector.end(), v.begin(), v.end() );
	return ;
}

unsigned int	Span::longestSpan( void )
{
	if (this->_size < 2)
		throw SizeTooLowException();
	return *std::max_element( this->_vector.begin(), this->_vector.end() )
			- *std::min_element( this->_vector.begin(), this->_vector.end() );
}

unsigned int	Span::shortestSpan( void )
{
	NAMESPACE::vector<int>	clone;
	unsigned int			shortest;
	unsigned int			lastest;

	if (this->_size < 2)
		throw SizeTooLowException();
	clone = this->_vector;
	std::sort( clone.begin(), clone.end() );
	for (NAMESPACE::vector<int>::const_iterator current = clone.begin(); current < clone.end() - 1; current++)
{
		lastest = *(current + 1) - *current;
		shortest = (shortest == 0) ? lastest : std::min(shortest, lastest);
	}
	return shortest;
}

const char	*Span::FullSizeException::what() const throw()
{
	return "cannot add more numbers";
}

const char	*Span::SizeTooLowException::what() const throw()
{
	return "too few numbers in the container";
}
