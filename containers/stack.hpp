#ifndef FT_STACK_HPP
# define FT_STACK_HPP

# include "vector.hpp"

namespace	ft
{
	template< typename Type, typename Container = ft::vector<Type> >
		class	stack
		{
		public:
			typedef Container									container_type;
			typedef typename container_type::value_type			value_type;
			typedef typename container_type::size_type			size_type;
			typedef typename container_type::reference			reference;
			typedef typename container_type::const_reference	const_reference;

		protected:
			container_type	c;

		public:
			explicit
			stack( const container_type& ctnr = container_type() )
			: c(ctnr)
			{}

			/*	default destructor	*/
			~stack( void )
			{}

			stack&
			operator=( const stack& other )
			{
				if (this != &other)
					this->c = other.c;
				return *this;
			}

			reference
			top( void )
			{
				return this->c.back();
			}

			const_reference
			top( void ) const
			{
				return this->c.back();
			}

			bool
			empty( void ) const
			{
				return this->c.empty();
			}

			size_type
			size( void ) const
			{
				return this->c.size();
			}

			void
			push( const value_type& value )
			{
				this->c.push_back(value);
			}

			void
			pop( void )
			{
				this->c.pop_back();
			}

			template< typename T, typename C >
				friend bool
				operator==( const stack<T, C>& lhs,
							const stack<T, C>& rhs );

			template< typename T, typename C >
				friend bool
				operator<( const stack<T, C>& lhs,
							const stack<T, C>& rhs );
		};

	template< typename Type, typename Container >
		inline bool
		operator==( const stack<Type, Container>& lhs,
					const stack<Type, Container>& rhs )
		{
			return lhs.c == rhs.c;
		}

	template< typename Type, typename Container >
		inline bool
		operator!=( const stack<Type, Container>& lhs,
					const stack<Type, Container>& rhs )
		{
			return !(lhs == rhs);
		}

	template< typename Type, typename Container >
		inline bool
		operator<( const stack<Type, Container>& lhs,
					const stack<Type, Container>& rhs )
		{
			return lhs.c < rhs.c;
		}

	template< typename Type, typename Container >
		inline bool
		operator<=( const stack<Type, Container>& lhs,
					const stack<Type, Container>& rhs )
		{
			return !(rhs < lhs);
		}

	template< typename Type, typename Container >
		inline bool
		operator>( const stack<Type, Container>& lhs,
					const stack<Type, Container>& rhs )
		{
			return rhs < lhs;
		}

	template< typename Type, typename Container >
		inline bool
		operator>=( const stack<Type, Container>& lhs,
					const stack<Type, Container>& rhs )
		{
			return !(lhs < rhs);
		}
}
#endif
