#ifndef FT_VECTOR_HPP
# define FT_VECTOR_HPP

# include <cstddef>
# include <memory>
# include <stdexcept>
# include <algorithm>
# include <iterator>
# include "ft_normal_iterator.hpp"
# include "ft_reverse_iterator.hpp"
# include "ft_lexicographical_compare.hpp"
# include "ft_equal.hpp"

namespace	ft
{
	template< typename T, typename Alloc = std::allocator<T> >
		struct	vector_base
		{
			typedef Alloc								allocator_type;
			typedef	typename allocator_type::pointer	pointer;
			typedef std::size_t							size_type;

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

			vector_base( size_type n, const allocator_type& a )
			: allocator(a)
			{
				this->start = this->allocate(n);
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
				this->deallocate(this->start, size_type(this->end_of_storage - this->start));
			}

			pointer
			allocate( size_type n )
			{
				return n != 0 ? this->allocator.allocate(n) : 0;
			}

			void
			deallocate( pointer ptr, size_type n )
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
			typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;
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
		//		this->deallocate(this->start, this->capacity());
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

						std::copy(other.begin(), other.end(), tmp);
					//	this->_range_copy_init(other.begin(), other.end(), tmp);
					//	this->_range_destroy(this->start, this->finish);
						this->deallocate(this->start, this->capacity());
						this->start = tmp;
						this->end_of_storage = this->start + other_len;
					}
					else
					{
						if ( other_len <= this->size() )
							this->_range_destroy(this->start, this->finish);
				//		this->_range_copy_init(other.begin(), other.end(), this->start);
						std::copy(other.begin(), other.end(), this->start);
					}
					this->finish = this->start + other_len;
				}
				return *this;
			}

		protected:
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
						this->deallocate(this->start, this->capacity());
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
				return this->allocator;
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
				return this->allocator.max_size();
			}

			void
			resize( size_type n, T value = T() )
			{
				if (n > this->size())
					this->insert(this->end(), n - this->size(), value);
				else if (n < this->size())
					this->_erase_at_end(this->start + n);
			}

			size_type
			capacity( void ) const
			{
				return size_type(this->end_of_storage - this->start);
			}

			bool
			empty( void ) const
			{
				return this->begin() == this->end();
			}

			void
			reserve( size_type n )
			{
//				if (n > this->max_size())
//					throw std::length_error("vector");
				if (n > this->capacity())
				{
					const size_type	old_size = this->size();
					pointer			tmp = this->allocate(n);

					std::copy(this->start, this->finish, tmp);
					this->deallocate(this->start, this->capacity());
					this->start = tmp;
					this->finish = this->start + old_size;
					this->end_of_storage = this->start + n;
				}
			}

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

		protected:
			void
			_range_check( size_type n ) const
			{
				if ( n >= this->size() )
					throw std::out_of_range("vector::_range_check");
			}

		public:
			reference
			at( size_type n )
			{
				this->_range_check(n);
				return (*this)[n];
			}

			const_reference
			at( size_type n ) const
			{
				this->_range_check(n);
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

			void
			pop_back()
			{
				--this->finish;
				this->allocator.destroy(this->finish);
			}

		protected:
			size_type
			_check_length( size_type n )
			{
				const size_type	cap = this->capacity() + this->capacity();
				const size_type	size = this->size() + n;

				if (this->max_size() - this->size() < n)
					throw std::length_error("vector");
				return cap < size ? size : cap;
			}

			void
			_resize_insert( iterator position, size_type n, const value_type& value )
			{
				const size_type	new_len = this->_check_length(n);
				const size_type	elems_before = position - this->begin();
				pointer			new_start(this->allocate(new_len));
				pointer			new_finish(new_start);
				pointer			new_mid(new_start + elems_before);

				new_finish = std::copy(this->start, position.base(),
									new_start);
				std::fill(new_mid, new_mid + n, value);
				new_finish += n;
				new_finish = std::copy(position.base(), this->finish,
									new_finish);
				this->deallocate(this->start,
							this->end_of_storage - this->start);
				this->start = new_start;
				this->finish = new_finish;
				this->end_of_storage = new_start + new_len;
			}

			void
			_insert_at_end( const value_type& value )
			{
				this->allocator.construct(this->finish, value);
				++this->finish;
			}

			void
			_insert_aux( iterator position, const value_type& value )
			{
				if (this->finish != this->end_of_storage)
				{
					this->allocator.construct(this->finish, *(this->finish - 1));
					++this->finish;
					std::copy_backward(position.base(), this->finish - 2, this->finish - 1);
					*position = value;
				}
				else
					this->_resize_insert(position, 1, value);
			}

		public:

			void
			push_back( const value_type& value )
			{
				if (this->finish != this->end_of_storage)
					this->_insert_at_end(value);
				else
					this->_insert_aux(this->end(), value);
			}

			iterator
			insert( iterator position, const value_type& value )
			{
				const size_type	n = position - this->begin();

				if (this->finish != this->end_of_storage
					&& position == this->end())
					this->_insert_at_end(value);
				else
					this->_insert_aux(position, value);
				return iterator(this->start + n);
			}

			void
			insert( iterator position, size_type n, const value_type& value )
			{
				if (n != 0)
				{
					if (this->capacity() - this->size() >= n)
					{
						std::copy_backward(position, this->end(),
										this->finish + difference_type(n));
						std::fill(position.base(), position.base() + n, value);
						this->finish += n;
					}
					else
						this->_resize_insert(position, n, value);
				}
			}
/*
			template< typename InputIterator >
				void
				insert( iterator position, InputIterator first, InputIterator last )
				{
					for (; first != last; ++first)
					{
						position = this->insert(position, *first);
						++position;
					}
				}
*/
			iterator
			erase( iterator position )
			{
				if (position != this->end())
				{
					if (position + 1 != this->end())
						std::copy(position + 1, this->finish, position);
					--this->finish;
					this->allocator.destroy(this->finish);
				}
			}

			iterator
			erase( iterator first, iterator last )
			{
				if (first != last)
				{
					if (last != this->end())
						std::copy(last, this->finish, first);
					this->_erase_at_end(first.base() + (this->finish - last.base()));
				}
			}

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
