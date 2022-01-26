#ifndef FT_MAP_HPP
# define FT_MAP_HPP

# include <functional>
# include "ft_pair.hpp"
# include "ft_tree.hpp"

namespace	ft
{
	template< typename Key, typename T, typename Compare = std::less<Key>,
			  typename Alloc = std::allocator<ft::pair<const Key, T> > >
		class	map
		{
		public:
			typedef Key															key_value;
			typedef T															mapped_value;
			typedef ft::pair<const key_value, mapped_value>						value_type;
			typedef Compare														key_compare;
			typedef Alloc														allocator_type;

		private:
			typedef typename allocator_type::rebind<value_type>::other			pair_allocator_type;
			typedef tree<key_type,mapped_value,key_compare,pair_allocator_type>	tree_type;

			tree_type	_tree;

		public:
			typedef pair_allocator_type::reference								reference;
			typedef pair_allocator_type::const_reference						const_reference;
			typedef pair_allocator_type::pointer								pointer;
			typedef pair_allocator_type::const_pointer							const_pointer;
			typedef	tree_type::iterator											iterator;
			typedef	tree_type::const_iterator									const_iterator;
			typedef	tree_type::reverse_iterator									reverse_iterator;
			typedef tree_type::const_reverse_iterator							const_reverse_iterator;
			typedef tree_type::size_type										size_type;
			typedef tree_type::difference_type									diferrence_type;

			/*	default_constructor	*/
			map()
			{}

			explicit
			map( const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type() )
			{
			}

			template< typename InputIterator >
				map( InputIterator first, InputIterator last,
					const key_compare& comp = key_compare(),
					const allocator_type& alloc = allocator_type() )
				{
				}

			map( const map& x )
			{
			}

			map&
			operator=( const map& x )
			{
			}

			allocator_type
			get_allocator( void ) const
			{
			}

			iterator
			begin( void )
			{
			}

			const_iterator
			begin( void ) const
			{
			}

			iterator
			end( void )
			{
			}

			const_iterator
			end( void ) const
			{
			}

			reverse_iterator
			rbegin( void )
			{
			}

			const_reverse_iterator
			rbegin( void ) const
			{
			}

			reverse_iterator
			rend( void )
			{
			}

			const_reverse_iterator
			rend( void ) const
			{
			}

			bool
			empty( void ) const
			{
			}

			size_type
			size( void ) const
			{
			}

			size_type
			max_size( void ) const
			{
			}

			mapped_type&
			operator[]( const key_type& k )
			{
			}

			void
			clear( void )
			{
			}

			ft::pair<iterator, bool>
			insert( const value_type& v )
			{
			}

			iterator
			insert( iterator position, const value_type& v )
			{
			}

			template< typename InputInterator >
				void
				insert( typename InputIterator first, InputIterator last )
				{
				}

			void
			erase( iterator position )
			{
			}

			size_type
			erase( const key_type& k )
			{
			}

			void
			erase( iterator first, iterator last )
			{
			}

			void
			swap( map& x )
			{
			}

			size_type
			count( const key_type& key ) const
			{
			}

			iterator
			find( const key_type& key )
			{
			}

			const_iterator
			find( const key_type& key ) const
			{
			}

			ft::pair<iterator,iterator>
			equal_range( const key_type& key )
			{
			}

			ft::pair<const_iterator,const_iterator>
			equal_range( const key_type& key ) const
			{
			}

			iterator
			lower_bound( const key_type& key )
			{
			}

			const_iterator
			lower_bound( const key_type& key ) const
			{
			}

			iterator
			upper_bound( const key_type& key )
			{
			}

			const_iterator
			upper_bound( const key_type& key ) const
			{
			}

			key_compare
			key_comp( void ) const
			{
			}

			value_compare
			value_comp( void ) const
			{
			}
		};

	template< typename Key, typename T, typename Compare, typename Alloc >
		inline bool
		operator==( const map<Key,T,Compare,Alloc>& lhs,
					const map<Key,T,Comapre,Alloc>& rhs )
		{
			return lhs._tree == rhs._tree;
		}
	
	template< typename Key, typename T, typename Compare, typename Alloc >
		inline bool
		operator!=( const map<Key,T,Compare,Alloc>& lhs,
					const map<Key,T,Compare,Alloc>& rhs )
		{
			return !(lhs == rhs);
		}

	template< typename Key, typename T, typename Compare, typename Alloc >
		inline bool
		operator<( const map<Key,T,Compare,Alloc>& lhs,
					const map<Key,T,Compare,Alloc>& rhs )
		{
			return lhs._tree < rhs._tree;
		}

	template< typename Key, typename T, typename Compare, typename Alloc >
		inline bool
		operator>( const map<Key,T,Compare,Alloc>& lhs,
					const map<Key,T,Compare,Alloc>& rhs )
		{
			return rhs < lhs;
		}

	template< typename Key, typename T, typename Compare, typename Alloc >
		inline bool
		operator<=( const map<Key,T,Compare,Alloc>& lhs,
					const map<Key,T,Compare,Alloc>& rhs )
		{
			return !(rhs < lhs);
		}

	template< typename Key, typename T, typename Compare, typename Alloc >
		inline bool
		operator>=( const map<Key,T,Compare,Alloc>& lhs,
					const map<Key,T,Compare,Alloc>& rhs )
		{
			return !(lhs < rhs);
		}

	template< typename Key, typename T, typename Compare, typename Alloc >
		inline void
		swap( map<Key,T,Compare,Alloc>& lhs, map<Key,T,Compare,Alloc>& rhs )
		{
			lhs.swap(rhs);
		}
}

#endif
