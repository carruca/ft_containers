#ifndef FT_REVERSE_ITERATOR_HPP
# define FT_REVERSE_ITERATOR_HPP

#include "ft_iterators_traits.hpp"
#include <iterator>

namespace	ft
{
	template< typename Iterator >
		class	reverse_iterator
		: public std::iterator< typename std::iterator_traits<Iterator>::iterator_category,
							typename std::iterator_traits<Iterator>::value_type,
							typename std::iterator_traits<Iterator>::difference_type,
							typename std::iterator_traits<Iterator>::pointer,
							typename std::iterator_traits<Iterator>::reference >
		{
		protected:
			Iterator	current;

			typedef ft::iterator_traits<Iterator>				traits_type;

		public:
			typedef Iterator									iterator_type;
			typedef typename traits_type::iterator_category		iterator_category;
			typedef typename traits_type::value_type			value_type;
			typedef typename traits_type::difference_type		difference_type;
			typedef typename traits_type::pointer				pointer;
			typedef typename traits_type::reference				reference;

			/*	default constructor	*/
			reverse_iterator( void ) : current()
			{}

			explicit reverse_iterator( iterator_type x ) : current( x )
			{}

			template< typename Iter >
				reverse_iterator( const reverse_iterator<Iter>& other ) : current( other.base() )
				{}

			template< typename Iter >
				reverse_iterator&
				operator=( const reverse_iterator<Iter>& other )
				{
					if ( this == &other )
						return *this;
					this->current = other.base();
					return *this;
				}

			iterator_type
			base( void ) const
			{
				return this->current;
			}

			/*	dereference operator */
			reference
			operator*( void ) const
			{
				Iterator	tmp = this->current;

				return *--tmp;
			}

			pointer
			operator->( void ) const
			{
				return &(operator*());
			}

			reverse_iterator&
			operator++( void )
			{
				--this->current;
				return *this;
			}

			reverse_iterator&
			operator--( void )
			{
				++this->current;
				return *this;
			}

			reverse_iterator
			operator++( int )
			{
				reverse_iterator	tmp = *this;

				--( *this );
				return tmp;
			}

			reverse_iterator
			operator--( int )
			{
				reverse_iterator	tmp = *this;

				++( *this );
				return tmp;
			}

			reverse_iterator
			operator+( difference_type n ) const
			{
				return reverse_iterator( this->base() - n );
			}

			reverse_iterator&
			operator+=( difference_type n )
			{
				this->current -= n;
				return *this;
			}

			reverse_iterator
			operator-( difference_type n ) const
			{
				return reverse_iterator( this->base() + n );
			}

			reverse_iterator&
			operator-=( difference_type n )
			{
				this->current += n;
				return *this;
			}

			reference
			operator[]( difference_type n ) const
			{
				return *(*this + n);
			}
		};

	template< typename Iterator >
		inline bool
		operator==( const reverse_iterator<Iterator>& lhs,
								const reverse_iterator<Iterator>& rhs )
		{
			return lhs.base() == rhs.base();
		}

	template< typename Iterator >
		inline bool
		operator!=( const reverse_iterator<Iterator>& lhs,
								const reverse_iterator<Iterator>& rhs )
		{
			return !(lhs == rhs);
		}

	template< typename Iterator >
		inline bool
		operator<( const reverse_iterator<Iterator>& lhs,
								const reverse_iterator<Iterator>& rhs )
		{
			return rhs.base() < lhs.base();
		}

	template< typename Iterator >
		inline bool
		operator<=( const reverse_iterator<Iterator>& lhs,
								const reverse_iterator<Iterator>& rhs )
		{
			return !(rhs < lhs);
		}

	template< typename Iterator >
		inline bool
		operator>( const reverse_iterator<Iterator>& lhs,
								const reverse_iterator<Iterator>& rhs )
		{
			return rhs < lhs;
		}

	template< typename Iterator >
		inline bool
		operator>=( const reverse_iterator<Iterator>& lhs,
								const reverse_iterator<Iterator>& rhs )
		{
			return !(lhs < rhs);
		}

	template< typename Iterator >
		inline typename reverse_iterator<Iterator>::difference_type
		operator-( const reverse_iterator<Iterator>& lhs,
					const reverse_iterator<Iterator>& rhs )
		{
			return rhs.base() - lhs.base();
		}

	template< typename Iterator >
		inline reverse_iterator<Iterator>
		operator+( typename reverse_iterator<Iterator>::difference_type n,
					const reverse_iterator<Iterator>& x )
		{
			return reverse_iterator<Iterator>( x.base() - n );
		}
};

#endif
