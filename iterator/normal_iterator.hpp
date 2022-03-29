#ifndef FT_NORMAL_ITERATOR_HPP
# define FT_NORMAL_ITERATOR_HPP

# include "iterators_traits.hpp"

namespace	ft
{
	template< typename Iterator, typename Container >
		class	normal_iterator
		{
		protected:
			Iterator	current;

		public:
			typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
			typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
			typedef typename ft::iterator_traits<Iterator>::reference			reference;

			normal_iterator( void )
			: current()
			{}

			explicit
			normal_iterator( const Iterator& x )
			: current(x)
			{}

			template< typename Iter >
				normal_iterator( const normal_iterator<Iter, Container>& other )
				: current(other.base())
				{}

			const Iterator&
			base( void ) const
			{
				return this->current;
			}

			reference
			operator*( void ) const
			{
				return *this->current;
			}

			pointer
			operator->( void ) const
			{
				return this->current;
			}

			normal_iterator&
			operator++( void )
			{
				++this->current;
				return *this;
			}

			normal_iterator&
			operator--( void )
			{
				--this->current;
				return *this;
			}

			normal_iterator
			operator++( int )
			{
				return normal_iterator(this->current++);
			}

			normal_iterator
			operator--( int )
			{
				return normal_iterator(this->current--);
			}

			normal_iterator
			operator+( difference_type n ) const
			{
				return normal_iterator(this->current + n);
			}

			normal_iterator&
			operator+=( difference_type n )
			{
				this->current += n;
				return *this;
			}

			normal_iterator
			operator-( difference_type n ) const
			{
				return normal_iterator(this->current - n);
			}

			normal_iterator&
			operator-=( difference_type n )
			{
				this->current -= n;
				return *this;
			}

			reference
			operator[]( difference_type n ) const
			{
				return this->current[n];
			}
		};

	template< typename IteratorL, typename IteratorR, typename Container >
		inline bool
		operator==( const normal_iterator<IteratorL, Container>& lhs,
			const normal_iterator<IteratorR, Container>& rhs )
		{
			return lhs.base() == rhs.base();
		}

	template< typename IteratorL, typename IteratorR, typename Container >
		inline bool
		operator!=( const normal_iterator<IteratorL, Container>& lhs,
			const normal_iterator<IteratorR, Container>& rhs )
		{
			return !(lhs == rhs);
		}

	template< typename IteratorL, typename IteratorR, typename Container >
		inline bool
		operator<( const normal_iterator<IteratorL, Container>& lhs,
			const normal_iterator<IteratorR, Container>& rhs )
		{
			return lhs.base() < rhs.base();
		}

	template< typename IteratorL, typename IteratorR, typename Container >
		inline bool
		operator<=( const normal_iterator<IteratorL, Container>& lhs,
			const normal_iterator<IteratorR, Container>& rhs )
		{
			return !(rhs < lhs);
		}

	template< typename IteratorL, typename IteratorR, typename Container >
		inline bool
		operator>( const normal_iterator<IteratorL, Container>& lhs,
			const normal_iterator<IteratorR, Container>& rhs )
		{
			return rhs < lhs;
		}

	template< typename IteratorL, typename IteratorR, typename Container >
		inline bool
		operator>=( const normal_iterator<IteratorL, Container>& lhs,
			const normal_iterator<IteratorR, Container>& rhs )
		{
			return !(lhs < rhs);
		}

	template< typename IteratorL, typename IteratorR, typename Container >
		inline typename normal_iterator<IteratorL, Container>::difference_type
		operator-( const normal_iterator<IteratorL, Container>& lhs,
			const normal_iterator<IteratorR, Container>& rhs )
		{
			return lhs.base() - rhs.base();
		}

	template< typename Iterator, typename Container >
		inline normal_iterator<Iterator, Container>
		operator+( typename normal_iterator<Iterator, Container>::difference_type n,
			const normal_iterator<Iterator, Container>& x )
		{
			return normal_iterator<Iterator, Container>(x.base() + n);
		}
}

#endif
