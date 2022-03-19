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
			container_type	container;

		public:
			explicit
			stack( const container_type& ctnr = container_type() )
			: container(ctnr)
			{}

			/*	default destructor	*/
			~stack( void )
			{}

			stack&
			operator=( const stack& other )
			{
				if (this != &other)
					this->container = other.container;
				return *this;
			}

			reference
			top( void )
			{
				return this->container.back();
			}

			const_reference
			top( void ) const
			{
				return this->container.back();
			}

			bool
			empty( void ) const
			{
				return this->container.empty();
			}

			size_type
			size( void ) const
			{
				return this->container.size();
			}

			void
			push( const value_type& value )
			{
				this->container.push_back(value);
			}

			void
			pop( void )
			{
				this->container.pop_back();
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
			return lhs.container == rhs.container;
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
			return lhs.container < rhs.container;
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
