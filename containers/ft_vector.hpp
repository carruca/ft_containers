#ifndef FT_VECTOR_HPP
# define FT_VECTOR_HPP

# include "ft_normal_iterator.hpp"
# include "ft_reverse_iterator.hpp"
# include "ft_lexicographical_compare.hpp"
# include "ft_equal.hpp"
# include "ft_is_integral.hpp"
# include "ft_enable_if.hpp"

# include <cstddef>
# include <memory>
# include <stdexcept>
# include <algorithm>
# include <iterator>

namespace	ft
{
	template< typename Type, typename Alloc = std::allocator<Type> >
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

			vector_base( size_type size, const allocator_type& a )
			: allocator(a)
			{
				this->start = this->allocate(size);
				this->finish = this->start;
				this->end_of_storage = this->start + size;
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
				if (ptr)
					this->allocator.deallocate(ptr, n);
			}
		};

	template< typename Type, typename Alloc = std::allocator<Type> >
		class	vector
			: protected vector_base<Type, Alloc>
		{

		public:
			typedef Type											value_type;
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

		protected:
			typedef vector_base<value_type, allocator_type>			base;

			void
			_fill_construct( pointer first, size_type nbr, const value_type& value )
			{
				pointer	current = first;

				for ( ; nbr > 0; --nbr, ++current )
					this->allocator.construct(current, value);
				this->finish = this->end_of_storage;
			}

			template< typename InputIterator >
				pointer
				_range_construct( InputIterator first, InputIterator last, pointer result )
				{
					pointer	current = result;

					for ( ; first != last; ++first, ++current )
						this->allocator.construct(current, *first);
					return current;
				}

			template< typename InputIterator >
				void
				_range_destroy( InputIterator first, pointer last )
				{
					pointer	current = first;

					for ( ; current != last; ++current )
						this->allocator.destroy(current);
				}

		public:
			/*	default constructor	*/
			vector( void )
			: base()
			{}

			explicit
			vector( const allocator_type& a )
			: base(a)
			{}

			explicit
			vector( size_type n, const value_type& value = value_type(),
					const allocator_type& a = allocator_type() )
			: base(n, a)
			{
				this->_fill_construct(this->start, n, value);
			}

			template< typename InputIterator >
				vector( typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first,
					InputIterator last, const allocator_type& a = allocator_type() )
				: base(std::distance(first, last), a)
				{
					this->finish = this->_range_construct(first, last, this->start);
				}

			vector( const vector& other )
			: base(other.size(), other.get_allocator())
			{
				this->finish = this->_range_construct(other.begin(), other.end(), this->start);
			}

			/*	default destructor	*/
			~vector( void )
			{}

			vector&
			operator=( const vector& other )
			{
				if ( this != &other )
				{
					const size_type	other_len = other.size();

					if ( other_len > this->capacity() )
					{
						pointer	tmp = this->allocate(other_len);

					//	std::copy(other.begin(), other.end(), tmp);
						this->_range_construct(other.begin(), other.end(), tmp);
						this->_range_destroy(this->start, this->finish);
						this->deallocate(this->start, this->capacity());
						this->start = tmp;
						this->end_of_storage = this->start + other_len;
					}
					else
					{
					//	if ( other_len <= this->size() )
						this->_range_destroy(this->start, this->finish);
						this->_range_construct(other.begin(), other.end(), this->start);
				//		std::copy(other.begin(), other.end(), this->start);
					}
					this->finish = this->start + other_len;
				}
				return *this;
			}

		protected:
			void
			_erase_at_end( pointer pos )
			{
				this->_range_destroy(pos, this->finish);
				this->finish = pos;
			}

			void
			_fill_assign( size_type len, const value_type& value )
			{
				if (len > this->capacity())
				{
					vector	tmp(len, value, this->get_allocator());

					tmp.swap(*this);
				}
				else
				{
				//	std::fill_n(this->start, n, value);
					this->_fill_construct(this->start, len, value);
					if (len > this->size())
						this->finish += (len - this->size());
					else
						this->_erase_at_end(this->start + len);
				}
			}

			template< typename InputIterator >
				void
				_range_assign( InputIterator first, InputIterator last)
				{
					InputIterator	mid = first;
					pointer			tmp;
					const size_type	len = std::distance(first, last);

					if ( len > this->capacity() )
					{
						tmp = this->allocate(len);
					//	std::copy(first, last, tmp);
						this->_range_construct(first, last, tmp);
						this->_range_destroy(this->start, this->finish);
						this->deallocate(this->start, this->capacity());
						this->start = tmp;
						this->finish = this->start + len;
						this->end_of_storage = this->start + len;
					}
					else if ( len <= this->size() )
					{
					//	std::copy(first, last, this->start);
						tmp = this->_range_construct(first, last, this->start);
						this->_erase_at_end(tmp);
					}
					else
					{
				//		mid = first;
						std::advance(mid, this->size());
				//		std::copy(first, mid, this->start);
						this->_range_construct(first, mid, this->start);
						this->finish = this->_range_construct(mid, last, this->finish);
					}
				}

		public:
			void
			assign( size_type len, const value_type& value )
			{
				this->_fill_assign(len, value);
			}

			template< typename InputIterator >
				void
				assign(
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first,
					InputIterator last ) //TODO el error de compilacion difiere con el std
				{
					this->_range_assign(first, last);
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
			resize( size_type len, value_type value = value_type() )
			{
				if (len > this->size())
					this->insert(this->end(), len - this->size(), value);
				else if (len < this->size())
					this->_erase_at_end(this->start + len);
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
			reserve( size_type cap )
			{
				if (cap > this->capacity())
				{
					const size_type	size = this->size();
					pointer			tmp = this->allocate(cap);

				//	std::copy(this->start, this->finish, tmp);
					this->_range_construct(this->start, this->finish, tmp);
					this->_range_destroy(this->start, this->finish);
					this->deallocate(this->start, this->capacity());
					this->start = tmp;
					this->finish = this->start + size;
					this->end_of_storage = this->start + cap;
				}
			}

			reference
			operator[]( size_type pos )
			{
				return *(this->start + pos);
			}

			const_reference
			operator[]( size_type pos ) const
			{
				return *(this->start + pos);
			}

		protected:
			void
			_range_check( size_type pos ) const
			{
				if ( pos >= this->size() )
					throw std::out_of_range("vector::_range_check");
			}

		public:
			reference
			at( size_type pos )
			{
				this->_range_check(pos);
				return (*this)[pos];
			}

			const_reference
			at( size_type pos ) const
			{
				this->_range_check(pos);
				return (*this)[pos];
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

			value_type*
			data( void )
			{
				return &this->front();
			}

			void
			pop_back( void )
			{
				--this->finish;
				this->allocator.destroy(this->finish);
			}

		protected:
			size_type
			_check_length( size_type len )
			{
				const size_type	cap = this->capacity() + this->capacity();
				const size_type	size = this->size() + len;

				if (this->max_size() - this->size() < len)
					throw std::length_error("vector");
				return (cap < size) ? size : cap;
			}

			void
			_resize_insert( iterator position, size_type len, const value_type& value )
			{
				const size_type	new_len(this->_check_length(len));
				const size_type	elems_before(position - this->begin());
				pointer			new_start(this->allocate(new_len));
				pointer			new_mid(new_start + elems_before);
				pointer			new_finish;

		//		new_finish = std::copy(this->start, position.base(), new_start);
				new_finish = this->_range_construct(this->start,
												position.base(), new_start);
		//		std::fill_n(new_mid, n, value);
				this->_fill_construct(new_mid, len, value);
				new_finish += len;
		//		new_finish = std::copy(position.base(), this->finish, new_finish);
				new_finish = this->_range_construct(position.base(),
												this->finish, new_finish);
				this->_range_destroy(this->start, this->finish);
				this->deallocate(this->start,
						this->end_of_storage - this->start);
				this->start = new_start;
				this->finish = new_finish;
				this->end_of_storage = this->start + new_len;
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
				const size_type	distance = position - this->begin();

				if (this->finish != this->end_of_storage
					&& position == this->end())
					this->_insert_at_end(value);
				else
					this->_insert_aux(position, value);
				return iterator(this->start + distance);
			}

			void
			insert( iterator position, size_type len, const value_type& value )
			{
				if (len != 0)
				{
					if (this->capacity() - this->size() >= len)
					{
						std::copy_backward(position, this->end(),
										this->finish + difference_type(len));
				//		std::fill(position.base(), position.base() + len, value);
						this->_fill_construct(position.base(), len, value);
						this->finish += len;
					}
					else
						this->_resize_insert(position, len, value);
				}
			}

			template< typename InputIterator >
				void
				insert( iterator position,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last )
				{
					for (; first != last; ++first)
					{
						position = this->insert(position, *first);
						++position;
					}
				}

			iterator
			erase( iterator position )
			{
				if (position != this->end())
				{
					if (position + 1 != this->end())
						std::copy(position.base() + 1, this->finish, position.base());
					--this->finish;
					this->allocator.destroy(this->finish);
				}
				return position;
			}

			iterator
			erase( iterator first, iterator last )
			{
				if (first != last)
				{
					if (last != this->end())
						std::copy(last.base(), this->finish, first.base());
					this->_erase_at_end(first.base() + (this->finish - last.base()));
				}
				return first;
			}

			void
			swap( vector& other )
			{
				std::swap(this->start, other.start);
				std::swap(this->finish, other.finish);
				std::swap(this->end_of_storage, other.end_of_storage);
				std::swap(this->allocator, other.allocator);
			}

			void
			clear( void )
			{
				this->_erase_at_end(this->start);
			}
		};

	template< typename T, typename Alloc >
		inline bool
		operator==( const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs )
		{
			return (lhs.size() == rhs.size()
				&& ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
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
			return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
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
