#ifndef FT_VECTOR_HPP
# define FT_VECTOR_HPP

# include <cstddef>
# include <memory>
# include <stdexcept>
# include <algorithm>
# include <iterator>
# include "ft_lexicographical_compare.hpp"
# include "ft_equal.hpp"

namespace	ft
{
	template< typename T, typename Alloc = std::allocator<T> >
		struct	vector_base
		{
			typedef Alloc								allocator_type;
			typedef	typename allocator_type::pointer	pointer;

			pointer			start;
			pointer			finish;
			pointer			end_of_storage;
			allocator_type	allocator;

			vector_base( void )
			: start(0)
			, finish(0)
			, end_of_storage(0)
			, allocator()
			{}

			vector_base( const allocator_type& a )
			: start(0)
			, finish(0)
			, end_of_storage(0)
			, allocator(a)
			{}

			vector_base( std::size_t n, const allocator_type& a )
			: allocator(a)
			{
				this->start = this->allocator.allocate(n);
				this->finish = this->start;
				this->end_of_storage = this->start + n;
			}

			vector_base( const vector_base& other )
			: start(other.start)
			, finish(other.finish)
			, end_of_storage(other.end_of_storage)
			, allocator(other.allocator)
			{}

			~vector_base( void )
			{
				this->deallocate(this->start, std::distance(this->end_of_storage - this->start));
			}

			pointer
			allocate( std::size_t n )
			{
				return n != 0 ? this->allocator.allocate(n) : 0;
			}

			void
			deallocate( pointer ptr, std::size_t n )
			{
				if ( ptr )
					this->allocator.deallocate(ptr, n);
			}
		};

	template< typename T, typename Alloc = std::allocator<T> >
		class	vector : protected vector_base<T, Alloc>
		{
			typedef vector_base<T, Alloc>							base;

		public:
			typedef T												value_type;
			typedef Alloc											allocator_type;
			typedef typename allocator_type::reference				reference;
			typedef typename allocator_type::const_reference		const_reference;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;
			typedef ft::normal_iterator<pointer, vector>			iterator;
			typedef ft::normal_iterator<const_pointer, vector>		const_iterator;
			typedef ft::reverse_iterator<iterator>					reverse_iterator;
			typedef ft::reverse_iterator<const_reverse_iterator>	const_reverse_iterator
			typedef std::size_t										size_type;
			typedef std::ptrdiff_t									difference_type;

			/*	default constructor	*/
			vector( void )
			: base()
			{}

			explicit
			vector( const Alloc& a )
			: base(a)
			{}

			explicit
			vector( size_type n, const T& value = T(), const Alloc& a = Alloc() )
			: base(n, a)
			{
				this->_fill_init(this->start, n, value);
			}

			template< typename InputIterator >
				vector( InputIterator first, InputIterator last, const Alloc& a = Alloc() )
				: base(std::distance(first, last), a)
				{
					this->finish = this->_range_copy_init(first, last, this->start);
				}

			vector( const vector& other )
			: base(other.size(), other.get_allocator())
			{
				this->finish = this->_range_copy_init(other.begin(), other.end(), this->start);
			}

			/*	default destructor	*/
			~vector( void )
			{
				this->_range_destroy(this->start, this->finish);
			}

			vector&
			operator=( const vector& other )
			{
				if ( this != &other )
				{
					const size_type	other_len = other.size();

					if ( other_len > this->capacity() )
					{
						pointer	tmp = this->allocate(other_len);

						this->_range_copy_init(other.begin(), other.end(), tmp);
						this->_range_destroy(this->start, this->finish);
						this->deallocate(this->start, std::distance(this->end_of_storage - this->start));
						this->start = tmp;
						this->end_of_storage = this->start + other_len;
					}
					else
					{
						if ( other_len <= this->size() )
							this->_range_destroy(this->start, this->finish);
						this->_range_copy_init(other.begin(), other.end(), this->start);
					}
					this->finish = this->start + other_len;
				}
				return *this;
			}

		private:
			allocator_type&
			_get_allocator( void )
			{
				return this->allocator;
			}

			void
			_fill_init( pointer first, size_type n, const value_type& value )
			{
				pointer	current = first;

				for ( ; n > 0; --n, ++current )
					this->allocator.construct(current, value);
				this->finish = this->end_of_storage;
			}

			void
			_fill_assign( size_type n, const value_type& value )
			{
				if ( n > this->capacity() )
				{
					vector	tmp(n, value, this->_get_allocator());

					tmp.swap(*this);
				}
				else if ( n > this->size() )
				{
					std::fill(this->begin(), this->end(), value);
					this->_fill_init(this->finish, n - this->size(), value);
					this->finish += n - this->size();
				}
				else
				{
					std::fill_n(this->start, n, value);
					this->_erase_at_end(this->start + n);
				}
			}

			template< typename InputIterator >
				void
				_range_fill_assign( InputIterator first, InputIterator last)
				{
					const size_type	len = std::distance(first, last);

					if ( len > this->capacity() )
					{
						pointer	tmp = this->allocate(len);

						this->_range_copy_init(first, last, tmp);
						this->_range_destroy(this->start, this->finish);
						this->deallocate(this->start, std::distance(this->end_of_storage - this->start));
						this->start = tmp;
						this->finish = this->start + len;
						this->end_of_storage = this->start + len;
					}
					else if ( len <= this->size() )
						this->erase_at_end(std::copy(first, last, this->start));
					else
					{
						InputIterator	mid = first;
						std::advance(mid, this->size());
						std::copy(first, mid, this->start);
						this->finish = this->_range_copy_init(mid, last, this->finish);
					}
				}

			template< typename InputIterator >
				pointer
				_range_copy_init( InputIterator first, InputIterator last, pointer result )
				{
					pointer	current = result;

					for ( ; first != last; ++first, ++current )
						this->allocator.construct(current, *first);
					return current;
				}

			template< typename InputIterator >
				void
				_range_destroy( InputIterator first, InputIterator last )
				{
					pointer	current = first;

					for ( ; current != last; ++current )
						this->allocator.destroy(current);
				}

			void
			_erase_at_end( pointer pos )
			{
				this->_range_destroy(pos, this->finish);
				this->finish = pos;
			}

		public:
			void
			assign( size_type n, const T& value )
			{
				this->_fill_assign(n, value);
			}

			template< typename InputIterator >
				void
				assign( InputIterator first, InputIterator last)
				{
					this->_range_fill_assign(first, last);
				}

			allocator_type
			get_allocator( void ) const
			{
				return this-allocator;
			}

			iterator
			begin( void )
			{
				return iterator(this->start);
			}

			const_iterator
			begin( void ) const
			{
				return const_iterator(this->start);
			}

			iterator
			end( void )
			{
				return iterator(this->finish);
			}

			const_iterator
			end( void ) const
			{
				return const_iterator(this->finish);
			}

			reverse_iterator
			rbegin( void )
			{
				return reverse_iterator(this->end());
			}

			const_reverse_iterator
			rbegin( void ) const
			{
				return const_reverse_iterator(this->end());
			}

			reverse_iterator
			rend( void )
			{
				return reverse_iterator(this->begin());
			}

			const_reverse_iterator
			rend( void ) const
			{
				return const_reverse_iterator(this->begin());
			}

			size_type
			size( void ) const
			{
				return size_type(this->finish - this->start);
			}

			size_type
			max_size( void ) const
			{
				return alloc.max_size();
			}

			void
			resize( size_type n, T value = T() )
			{
				if (n > this->size())
				{
					//insert
				}
				else if (n < this->size())
					this->_erase_at_end(this->start + n);
			}

			size_type
			capacity( void ) const
			{
				return size_type(this->end_of_capacity - this->start);
			}

			bool
			empty( void ) const
			{
				return this->begin() == this->end();
			}
/*
			void
			reserve( size_type n )
			{}
*/
			reference
			operator[]( size_type n )
			{
				return *(this->start + n);
			}

			const_reference
			operator[]( size_type n ) const
			{
				return *(this->start + n);
			}

			reference
			at( size_type n )
			{
				if ( n >= this->size() )
					throw std::out_of_range();
				return (*this)[n];
			}

			const_reference
			at( size_type n ) const
			{
				if ( n >= this->size() )
					throw std::out_of_range();
				return (*this)[n];
			}

			reference
			front( void )
			{
				return *this->begin();
			}

			const_reference
			front( void ) const
			{
				return *this->begin();
			}

			reference
			back( void )
			{
				return *(this->end() - 1);
			}

			const_reference
			back( void ) const
			{
				return *(this->end() - 1);
			}

			T*
			data( void )
			{
				return &this->front();
			}
/*
			void
			push_back( const value_type& x )
			{}

			void
			pop_back()
			{}

			iterator
			insert( iterator position, const value_type& x )
			{}

			void
			insert( iterator position, size_type n, const value_type& x )
			{}

			template< typename InputIterator >
				void
				insert( iterator pos, InputIterator first, InputIterator last )
				{}

			iterator
			erase( iterator position )
			{}

			iterator
			erase( iterator first, iterator last )
			{}
*/
			void
			swap( vector& other )
			{
				std::swap(this->start, other.start);
				std::swap(this->finish. other.finish);
				std::swap(this->end_of_storage, other.end_of_storage);
				std::swap(this->allocator, other.allocator);
			}

			void
			clear( void )
			{
				this->erase_at_end(this->start);
			}

		};

	template< typename T, typename Alloc >
		inline bool
		operator==( const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs )
		{
			return (lhs.size() == rhs.size()
				&& std::equal(lhs.begin(), lhs.end(), rhs.begin())); //cambiar por ft namespace
		}

	template< typename T, typename Alloc >
		inline bool
		operator!=( const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs )
		{
			return !(lhs == rhs);
		}

	template< typename T, typename Alloc >
		inline bool
		operator<( const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs )
		{
			return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); //cambiar por ft namespace
		}

	template< typename T, typename Alloc >
		inline bool
		operator>( const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs )
		{
			return rhs < lhs;
		}

	template< typename T, typename Alloc >
		inline bool
		operator<=( const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs )
		{
			return !(rhs < lhs);
		}

	template< typename T, typename Alloc >
		inline bool
		operator>=( const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs )
		{
			return !(lhs < rhs);
		}

	template< typename T, typename Alloc >
		inline void
		swap( vector<T, Alloc>& lhs, vector<T, Alloc>& rhs)
		{
			lhs.swap(rhs);
		}
}

#endif
