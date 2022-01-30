#ifndef FT_TREE_HPP
# define FT_TREE_HPP

# include <cstddef>
# include <memory>
# include "ft_tree_iterator.hpp"
# include "ft_reverse_iterator.hpp"
# include "ft_equal.hpp"
# include "ft_lexicographical_compare.hpp"

namespace	ft
{
	enum	tree_color
	{
		red = false,
		black = true
	};

	template< typename Value >
		struct	tree_node
		{
			typedef struct tree_node*	node_ptr;

			tree_color	color;
			node_ptr	parent;
			node_ptr	left;
			node_ptr	right;
			Value		content;

			static node_ptr
			minimum( node_ptr x )
			{
				while (x->left != 0)
					x = x->left;
				return x;
			}

			static const_node_ptr
			minimum( node_ptr x )
			{
				while (x->left != 0)
					x = x->left;
				return x;
			}

			static node_ptr
			maximum( node_ptr x )
			{
				while (x->right != 0)
					x = x->right;
				return x;
			}

			static const_node_ptr
			maximum( node_ptr x )
			{
				while (x->right != 0)
					x = x->right;
				return x;
			}

			static node_ptr
			increment( node_ptr x )
			{
				node_ptr	y;

				if (x->right != 0)
					return tree_node::mininum(x->right);
				y = x->parent;
				while ( y != 0 && x == y->right)
				{
					x = y;
					y = x->parent;
				}
				return y;
			}

			static node_ptr
			decrement( node_ptr x )
			{
				node_ptr	y;

				if (x->left != 0)
					return tree_node::maximum(x->left);
				y = x->parent;
				while ( y != 0 && x == y->left)
				{
					x = y;
					y = x->parent;
				}
				return y;
			}
		};

	template< typename Key, typename Value, typename Compare,
			  typename Alloc = std::allocator<Value> >
		class	tree
		{
		private:
			typedef typename Alloc::rebind<tree_node_type>::other	node_allocator;

		public:
			typedef Key												key_type;
			typedef Value											value_type;
			typedef value_type*										pointer;
			typedef const value_type*								const_pointer;
			typedef value_type&										reference;
			typedef const value_type&								const_reference;
			typedef tree_node<value_type>							tree_node_type;
			typedef tree_node_type*									node_ptr;
			typedef const tree_node_type*							const_node_ptr;
			typedef std::size_t										size_type;
			typedef std::ptrdiff_t									difference_type;
			typedef	Alloc											allocator_type;
			typedef ft::tree_iterator<value_type>					iterator;
			typedef ft::tree_const_iterator<value_type>				const_iterator;
			typedef ft::reverse_iterator<iterator>					reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;

		protected:
			Compare			_key_compare;
			tree_node_type	_header;
			size_type		_node_count;
			node_allocator	_allocator;

			node_ptr
			_get_node( void )
			{
				return this->_allocator.allocate(1);
			}

			void
			_destroy_node( node_ptr x )
			{
				this->allocator.deallocate(x, 1);
			}

			node_ptr
			_create_node( const value_type& value )
			{
				node_ptr	tmp = this->_get_node();

				tmp->content = value;
				return tmp;
			}

			node_ptr
			_clone_node( node_ptr x )
			{
				node_ptr	tmp = this->_create_node(x->content);

				tmp->color = x->color;
				tmp->left = 0;
				tmp->right = 0;
				return tmp;
			}
/*
			void
			_empty_init( void )
			{
				this->_header.color = red;
				this->_header.parent = 0;
				this->_header.left = &this->_header;
				this->_header.right = &this->_header;
			}
*/
			node_ptr
			_root( void )
			{
				return this->_header.parent;
			}

			const_node_ptr
			_root( void ) const
			{
				return this->_header.parent;
			}

			node_ptr
			_minimum( node_ptr x )
			{
				return tree_node::minimum(x);
			}

			const_node_ptr
			_minimum( node_ptr x )
			{
				return tree_node::minimum(x);
			}

			node_ptr
			_maximum( node_ptr x )
			{
				return tree_node::maximum(x);
			}

			const_node_ptr
			_maximum( node_ptr x )
			{
				return tree_node::maximum(x);
			}
/*
			static node_ptr
			_increment( node_ptr x )
			{
				node_ptr	y;

				if (x->right != 0)
					return this->_mininum(x->right);
				y = x->parent;
				while ( y != 0 && x == y->right)
				{
					x = y;
					y = x->parent;
				}
				return y;
			}

			static node_ptr
			_decrement( node_ptr x )
			{
				node_ptr	y;

				if (x->left != 0)
					return this->_maximum(x->left);
				y = x->parent;
				while ( y != 0 && x == y->left)
				{
					x = y;
					y = x->parent;
				}
				return y;
			}
*/
			static void
			_rotate_left( node_ptr x, node_ptr root )
			{
				node_ptr	y = x->right;

				x->right = y->left;
				if (y->left != 0)
					y->left->parent = x;
				y->parent = x->parent;
				if (x == root)
					root = y;
				else if (x == x->parent->left)
					x->parent->left = y;
				else
					x->parent->right = y;
				y->left = x;
				x->parent = y;
			}

			static void
			_rotate_right( node_ptr x, node_ptr root )
			{
				node_ptr	y = x->left;

				x->left = y->right;
				if (y->right != 0)
					y->right->parent = x;
				y->parent = x->parent;
				if (x == root)
					root = y;
				else if (x == x->parent->right)
					x->parent->right = y;
				else
					x->parent->left = y;
				y->right = x;
				x->parent = y;
			}

		public:

			/*	default constructor	*/
			tree( void )
			{}

			tree( const Compare& comp)
			: _key_compare(comp),
			, _node_count(0)
			{
			}

			tree( const Compare& comp, const allocator_type& a )
			: _key_compare(comp)
			, _node_count(0)
			, allocator(a)
			{
			}

			tree( const tree<Key, Value, Compare, Alloc>& x )
			{
			}

			~tree( void )
			{
				//call erase
			}

			const tree<Key, Value, Compare, Alloc>&
			operator=( const tree<Key, value, Compare, Alloc>& rhs)
			{
			}

			allocator_type
			get_allocator( void ) const
			{
				return this->_allocator;
			}

			iterator
			begin( void )
			{
				return iterator(this->_minimum(this->_root()));
			}

			const_iterator
			begin( void ) const
			{
				return const_iterator(this->_minimum(this->_root()));
			}

			iterator
			end( void )
			{
				return iterator(this->_maximum(this->_root()));
			}

			const_iterator
			end( void ) const
			{
				return const_iterator(this->_maximum(this->_root()));
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

			bool
			empty( void ) const
			{
				return this->_node_count == 0;
			}

			size_type
			size( void )
			{
				return this->_node_count;
			}

			size_type
			max_size( void )
			{
				return size_type(-1);
			}

			void
			clear( void )
			{
				this->erase(this->begin());
				//incomplete
			}

			ft::pair<iterator, bool>
			insert( const value_type& value )
			{
			}

			iterator
			insert( iterator position, const value_type& value )
			{
			}

			template< typename InputIterator >
				void
				insert( InputIterator first, InputIterator last)
				{
				}

			void
			erase( iterator position )
			{
			}

			size_type
			erase( const key_type& key )
			{
			}

			void
			erase( iterator first, iterator last )
			{
			}

			void
			swap( tree<Key, Value, Compare, Alloc>& x )
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

			ft::pair<iterator, iterator>
			equal_range( const key_type& key )
			{
				node_ptr	x = this->begin();
				node_ptr	y = this->end();

				while (x != 0)
				{
					//TODO
				}
				return ft::pair<iterator,
					iterator>(iterator(x), iterator(y));
			}

			ft::pair<const_iterator, const_iterator>
			equal_range( const key_type& key ) const
			{
				const_node_ptr	x = this->begin();
				const_node_ptr	y = this->end();

				while (x != 0)
				{
					//TODO
				}
				return ft::pair<const_iterator,
					const_iterator>(const_iterator(x), const_iterator(y));
			}

		public:
			iterator
			lower_bound( const key_type& key )
			{
				node_ptr	x = this->_root();
				node_ptr	y = this->end();

				while (x != 0)
				{
					if (!this->_key_compare(x->content.first, key))
					{
						y = x;
						x = x->left;
					}
					else
						x = x->right;
				}
				return iterator(y);
			}

			const_iterator
			lower_bound( const key_type& key ) const
			{
				node_ptr	x = this->_root();
				node_ptr	y = this->end();

				while (x != 0)
				{
					if (!this->_key_compare(x->content.first, key))
					{
						y = x;
						x = x->left;
					}
					else
						x = x->right;
				}
				return const_iterator(y);
			}

			iterator
			upper_bound( const key_type& key )
			{
				node_ptr	x = this->_root();
				node_ptr	y = this->end();

				while (x != 0)
				{
					if (this->_key_compare(key, x->content.first))
					{
						y = x;
						x = x->left;
					}
					else
						x = x->right;
				}
				return iterator(y);
			}

			const_iterator
			upper_bound( const key_type& key ) const
			{
				node_ptr	x = this->_root();
				node_ptr	y = this->end();

				while (x != 0)
				{
					if (this->_key_compare(key, x->content.first))
					{
						y = x;
						x = x->left;
					}
					else
						x = x->right;
				}
				return const_iterator(y);
			}

			key_compare
			key_comp( void ) const
			{
				return this->key_compare;
			}
		};

	template< typename Key, typename Value, typename Compare, typename Alloc >
		inline bool
		operator==( const tree<Key,Value,Compare,Alloc>& lhs,
					const tree<Key,Value,Compare,Alloc>& rhs )
		{
			return lhs.size() == rhs.size()
				&& ft::equal(lhs.begin(), lhs.end(), rhs.begin();
		}

	template< typename Key, typename Value, typename Compare, typename Alloc >
		inline bool
		operator!=( const tree<Key,Value,Compare,Alloc>& lhs,
					const tree<Key,Value,Compare,Alloc>& rhs )
		{
			return !(lhs == rhs);
		}

	template< typename Key, typename Value, typename Compare, typename Alloc >
		inline bool
		operator<( const tree<Key,Value,Compare,Alloc>& lhs,
					const tree<Key,Value,Compare,Alloc>& rhs )
		{
			return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
		}

	template< typename Key, typename Value, typename Compare, typename Alloc >
		inline bool
		operator>( const tree<Key,Value,Compare,Alloc>& lhs,
					const tree<Key,Value,Compare,Alloc>& rhs )
		{
			return rhs < lhs;
		}

	template< typename Key, typename Value, typename Compare, typename Alloc >
		inline bool
		operator<=( const tree<Key,Value,Compare,Alloc>& lhs,
					const tree<Key,Value,Compare,Alloc>& rhs )
		{
			return !(rhs < lhs);
		}

	template< typename Key, typename Value, typename Compare, typename Alloc >
		inline bool
		operator>=( const tree<Key,Value,Compare,Alloc>& lhs,
					const tree<Key,Value,Compare,Alloc>& rhs )
		{
			return !(lhs < rhs);
		}

	template< typename Key, typename Value, typename Compare, typename Alloc >
		inline void
		swap( tree<Key,Value,Compare,Alloc>& lhs,
				tree<Key,Value,Compare,Alloc>& rhs )
		{
			return lhs.swap(rhs);
		}
}

#endif
