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
			typedef Key															key_type;
			typedef T															mapped_type;
			typedef ft::pair<const key_type, mapped_type>						value_type;
			typedef Compare														key_compare;
			typedef Alloc														allocator_type;

		private:
			typedef typename allocator_type::template rebind<value_type>::other	pair_allocator_type;
			typedef tree<key_type,mapped_type,key_compare,pair_allocator_type>	tree_type;

			tree_type	_tree;

		public:
			typedef typename pair_allocator_type::reference						reference;
			typedef typename pair_allocator_type::const_reference				const_reference;
			typedef typename pair_allocator_type::pointer						pointer;
			typedef typename pair_allocator_type::const_pointer					const_pointer;
			typedef	typename tree_type::iterator								iterator;
			typedef	typename tree_type::const_iterator							const_iterator;
			typedef	typename tree_type::reverse_iterator						reverse_iterator;
			typedef typename tree_type::const_reverse_iterator					const_reverse_iterator;
			typedef typename tree_type::size_type								size_type;
			typedef typename tree_type::difference_type							diferrence_type;

			class	value_compare
				: public std::binary_function<value_type, value_type, bool>
			{
				friend class map;

			protected:
				key_compare	comp;

				value_compare( key_compare c )
				: comp(c)
				{}

			public:
				typedef bool		result_type;
				typedef value_type	first_argument_type;
				typedef value_type	second_argument_type;

				bool
				operator()( const first_argument_type& x, const second_argument_type& y ) const
				{
					return comp(x.first, y.first);
				}
			};

			/*	default_constructor	*/
			map( void )
			: _tree()
			{}

			explicit
			map( const key_compare& comp, const allocator_type& a )
			: _tree(comp, a)
			{
			}
/*
			template< typename InputIterator >
				map( InputIterator first, InputIterator last,
					const key_compare& comp = key_compare(),
					const allocator_type& alloc = allocator_type() )
				{
				}

			map( const map& x )
			{
			}
*/
			/*	default destructor	*/
			~map( void )
			{}

			map&
			operator=( const map& x )
			{
				if (this != &x)
					this->_tree = x._tree;
				return *this;
			}

			allocator_type
			get_allocator( void ) const
			{
				return this->_tree.get_allocator();
			}

			iterator
			begin( void )
			{
				return this->_tree.begin();
			}

			const_iterator
			begin( void ) const
			{
				return this->_tree.begin();
			}

			iterator
			end( void )
			{
				return this->_tree.end();
			}

			const_iterator
			end( void ) const
			{
				return this->_tree.end();
			}

			reverse_iterator
			rbegin( void )
			{
				return this->_tree.rbegin();
			}

			const_reverse_iterator
			rbegin( void ) const
			{
				return this->_tree.rbegin();
			}

			reverse_iterator
			rend( void )
			{
				return this->_tree.rend();
			}

			const_reverse_iterator
			rend( void ) const
			{
				return this->_tree.rend();
			}

			bool
			empty( void ) const
			{
				return this->_tree.empty();
			}

			size_type
			size( void ) const
			{
				return this->_tree.size();
			}

			size_type
			max_size( void ) const
			{
				return this->_tree.max_size();
			}

			mapped_type&
			operator[]( const key_type& k )
			{
				iterator	it = this->find(k);

				if (it != this->end())
					return it->second;
				return insert(value_type(k,mapped_type())).first->second;
			}

			void
			clear( void )
			{
				this->_tree.clear();
			}

			ft::pair<iterator, bool>
			insert( const value_type& value )
			{
				ft::pair<iterator, bool>	ret(this->_tree.insert(value));

				this->_tree.debug();
				return ret;
			}

			iterator
			insert( iterator position, const value_type& value )
			{
				iterator	ret(this->_tree.insert(position, value));

				this->_tree.debug();
				return ret;
			}

			template< typename InputIterator >
				void
				insert( InputIterator first, InputIterator last )
				{
					this->_tree.insert(first, last);
				}

			void
			erase( iterator position )
			{
				this->_tree.erase(position);
			}

			size_type
			erase( const key_type& key )
			{
				this->_tree.erase(key);
			}

			void
			erase( iterator first, iterator last )
			{
				this->_tree.erase(first, last);
			}

			void
			swap( map& x )
			{
				this->_tree.swap(x._tree);
			}

			size_type
			count( const key_type& key ) const
			{
				this->_tree.count(key);
			}

			iterator
			find( const key_type& key )
			{
				return this->_tree.find(key);
			}

			const_iterator
			find( const key_type& key ) const
			{
				return this->_tree.find(key);
			}

			ft::pair<iterator,iterator>
			equal_range( const key_type& key )
			{
				this->_tree.equal_range(key);
			}

			ft::pair<const_iterator,const_iterator>
			equal_range( const key_type& key ) const
			{
				this->_tree.equal_range(key);
			}

			iterator
			lower_bound( const key_type& key )
			{
				this->_tree.lower_bound(key);
			}

			const_iterator
			lower_bound( const key_type& key ) const
			{
				this->_tree.lower_bound(key);
			}

			iterator
			upper_bound( const key_type& key )
			{
				this->_tree.upper_bound(key);
			}

			const_iterator
			upper_bound( const key_type& key ) const
			{
				this->_tree.upper_bound(key);
			}

			key_compare
			key_comp( void ) const
			{
				return this->_tree.key_comp();
			}
/*
			value_compare
			value_comp( void ) const
			{
				return value_compare(this->_tree.key_comp());
			}
*/
		};

	template< typename Key, typename T, typename Compare, typename Alloc >
		inline bool
		operator==( const map<Key,T,Compare,Alloc>& lhs,
					const map<Key,T,Compare,Alloc>& rhs )
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
