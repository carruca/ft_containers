#ifndef FT_VECTOR_HPP
# define FT_VECTOR_HPP

# include <cstddef>

namespace	ft
{
	template< typename T, typename Alloc = std::allocator<T> >
		class	vector
	{
	protected:
		Alloc	alloc;

	public:
		typedef T												value_type;
		typedef Alloc											allocator_type;
		typedef allocator_type::reference						reference;
		typedef allocator_type::const_reference					const_reference;
		typedef allocator_type::pointer							pointer;
		typedef allocator_type::const_pointer					const_pointer;
//		typedef 												iterator;
//		typedef													const_iterator;
		typedef ft::reverse_iterator<iterator>					reverse_iterator;
		typedef ft::reverse_iterator<const_reverse_iterator>	const_reverse_iterator
		typedef std::size_t										size_type;
		typedef std::ptrdiff_t									difference_type;

		/*	default constructor	*/
		vector( void )
		: alloc() {}

		explicit
		vector( const Alloc& a )
		: alloc(a) {}

		explicit
		vector( size_type n, const T& value = T(), const Alloc& a = Alloc() )
		{}

		template< typename InputIterator >
			vector( InputIterator first, InputIterator last, const Alloc& a = Alloc() )
			{}

		vector( const vector& other )
		{}

		/*	default destructor	*/
		~vector( void )
		{}

		vector&
		operator=( const vector& other )
		{
			return *this;
		}

		void
		assign( size_type n, const T& value )
		{}

		template< typename InputIterator >
			void
			assign( InputIterator first, InputIterator last)
			{}

		allocator_type
		get_allocator( void ) const
		{
			return alloc;
		}

		iterator
		begin( void )
		{}

		const_iterator
		begin( void ) const
		{}

		iterator
		end( void )
		{}

		const_iterator
		end( void ) const
		{}

		reverse_iterator
		rbegin( void )
		{}

		const_reverse_iterator
		rbegin( void ) const
		{}

		reverse_iterator
		rend( void )
		{}

		const_reverse_iterator
		rend( void ) const
		{}

		size_type
		size( void ) const
		{}

		size_type
		max_size( void ) const
		{
			return alloc.max_size();
		}

		void
		resize( size_type n, T value = T() )
		{}

		size_type
		capacity( void ) const
		{}

		bool
		empty( void ) const
		{
			return this->begin() == this->end();
		}

		void
		reserve( size_type n )
		{}
	};
}

#endif
