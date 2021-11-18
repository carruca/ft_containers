#ifndef FT_REVERSE_ITERATOR_HPP
# define FT_REVERSE_ITERATOR_HPP

namespace	ft
{
	template< typename Iterator >
		class	reverse_iterator
		: public std::iterator< ft::iterator_traits<Iterator>::iterator_category,
							ft::iterator_traits<Iterator>::value_type,
							ft::iterator_traits<Iterator>::difference_category,
							ft::iterator_traits<Iterator>::pointer,
							ft::iterator_traits<Iterator>::reference >
		{
		protected:
			Iterator	current;

		public:
			typedef typename Iterator											iterator_type;
			typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
			typedef typename ft::iterator_traits<Iterator>::difference_category	difference_category;
			typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
			typedef typename ft::iterator_traits<Iterator>::reference			reference;

			/*	default constructor	*/
			reverse_iterator( void ) : current()
			{}

			explicit reverse_iterator( iterator_type x ) : current( x )
			{}

			template< typename Iter >
				reverse_iterator( const reverse_iterator<Iter>& other ) : current( other.base() )
				{}

			template< typename Iter >
				reverse_iterator&	operator=( const reverse_iterator<Iter>& other )
				{
					if ( this = &other )
						return *this;
					this->current = other.base();
					return *this;
				}

			iterator_type	base( void ) const
			{
				return this->current;
			}

			/*	dereference operator */
			reference	operator*( void ) const
			{
				Iterator	tmp = this-	>current;

				return *--tmp;
			}

			pointer	operator->( void ) const
			{
				return &(operator*());
			}

			reverse_iterator&	operator++( void )
			{
				--this->current;
				return *this;
			}

			reverse_iterator&	operator--( void )
			{
				++this->current;
				return *this;
			}

			reverse_iterator	operator++( int )
			{
				reverse_iterator	tmp = *this;

				--( *this );
				return tmp;
			}

			reverse_iterator	operator--( int )
			{
				reverse_iterator	tmp = *this;

				++( *this );
				return tmp;
			}

			reverse_iterator	operator+( difference_type n ) const
			{
				return reverse_iterator( this->base() - n );
			}

			reverse_iterator&	operator+=( difference_type n )
			{
				this->current -= n;
				return *this;
			}

			reverse_iterator	operator-( difference_type n ) const
			{
				return reverse_iterator( this->base() + n );
			}

			reverse_iterator&	operator-=( difference_type n )
			{
				this->current += n;
				return *this;
			}

			reference			operator[]( difference_type n ) const
			{
				return *(*this + n);
			}
		};

	template< typename Iterator >
		inline bool	operator==( const reverse_iterator<Iterator>& lhs,
								const reverse_iterator<Iterator>& rhs )
		{
			return lhs.base() == rhs.base();
		}

	template< typename Iterator >
		inline bool	operator!=( const reverse_iterator<Iterator>& lhs,
								const reverse_iterator<Iterator>& rhs )
		{
			return lhs.base() != rhs.base();
		}

	template< typename Iterator >
		inline bool	operator>( const reverse_iterator<Iterator>& lhs,
								const reverse_iterator<Iterator>& rhs )
		{
			return lhs.base() < rhs.base();
		}

	template< typename Iterator >
		inline bool	operator>=( const reverse_iterator<Iterator>& lhs,
								const reverse_iterator<Iterator>& rhs )
		{
			return !(lhs.base() < rhs.base());
		}

	template< typename Iterator >
		inline bool	operator<( const reverse_iterator<Iterator>& lhs,
								const reverse_iterator<Iterator>& rhs )
		{
			return lhs.base() < rhs.base();
		}
};

#endif
