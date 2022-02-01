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
					return mininum(x->right);
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
					return maximum(x->left);
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
		public:
			typedef Key												key_type;
			typedef Value											value_type;
			typedef value_type*										pointer;
			typedef const value_type*								const_pointer;
			typedef value_type&										reference;
			typedef const value_type&								const_reference;
			typedef tree_node<value_type>							tree_node_type;
			typedef tree_node_type*									node_ptr;
			typedef tree_node_type&									node_ref;
			typedef const tree_node_type*							const_node_ptr;
			typedef std::size_t										size_type;
			typedef std::ptrdiff_t									difference_type;
			typedef	Alloc											allocator_type;
			typedef ft::tree_iterator<value_type>					iterator;
			typedef ft::tree_const_iterator<value_type>				const_iterator;
			typedef ft::reverse_iterator<iterator>					reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;

		private:
			typedef allocator_type::rebind<tree_node_type>::other	node_allocator;

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
			_leftmost( void )
			{
				return this->_header.left;
			}

			const_node_ptr
			_leftmost( void ) const
			{
				return this->_header.left;
			}

			node_ptr
			_rightmost( void )
			{
				return this->_header.right;
			}

			const_node_ptr
			_rightmost( void ) const
			{
				return this->_header.right;
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

			node_ptr
			_increment( node_ptr x )
			{
				return tree_node::increment(x);
			}

			node_ptr
			_decrement( node_ptr x )
			{
				return tree_node::decrement(x);
			}

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

			static void
			_insert_and_rebalance( const bool insert_left, node_ptr x, node_ref

		public:
			/*	default constructor	*/
			tree( void )
			{}

			tree( const Compare& comp)
			: _key_compare(comp)
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
				return iterator(this->_maximum(this->_root())->right); //no good
			}

			const_iterator
			end( void ) const
			{
				return const_iterator(this->_maximum(this->_root())->right); //no good
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
				node_ptr	x = this->_root();

				while (x != 0)
				{
					if (this->_key_compare(key, x->content.first))
						x = x->left;
					else if (this->_key_compare(x->content.first, key)
						x = x->right;
					else
						return 1;
				}
				return 0;
			}

			iterator
			find( const key_type& key )
			{
				iterator	it = this->_lower_bound(key, this->_root(), this->end());

				if (it != this->end() && !this->_key_compare(key, it->first))
					return it;
				return this->end();
			}

			const_iterator
			find( const key_type& key ) const
			{
				const_iterator	it = this->_lower_bound(key, this->_root(), this->end());

				if (it != this->end() && !this->_key_compare(key, it->first))
					return it;
				return this->end();
			}

			ft::pair<iterator, iterator>
			equal_range( const key_type& key )
			{
				typedef ft::pair<iterator, iterator>	pair_type;

				node_ptr	root = this->_root();
				node_ptr	result = this->end();

				while (root != 0)
				{
					if (this->_key_compare(key, root->content.first))
					{
						result = root;
						root = root->left;
					}
					else if (this->_key_compare(root->content.first, key)
						root = root->right;
					else
						return pair_type(iterator(root),
								iterator(root->right != 0 ? root->right : result))
				}
				return pair_type(iterator(result), iterator(result));
			}

			ft::pair<const_iterator, const_iterator>
			equal_range( const key_type& key ) const
			{
				typedef ft::pair<const_iterator, const_iterator>	pair_type;

				node_ptr	root = this->_root();
				node_ptr	result = this->end();

				while (root != 0)
				{
					if (this->_key_compare(key, root->content.first))
					{
						result = root;
						root = root->left;
					}
					else if (this->_key_compare(root->content.first, key)
						root = root->right;
					else
						return pair_type(const_iterator(root),
								const_iterator(root->right != 0 ? root->right : result))
				}
				return pair_type(const_iterator(result), const_iterator(result));
			}

		protected:
			iterator
			_lower_bound( const key_type& key, node_ptr root, node_ptr result )
			{
				while (root != 0)
				{
					if (!this->_key_compare(root->content.first, key))
					{
						result = root;
						root = root->left;
					}
					else
						root = root->right;
				}
				return iterator(result);
			}

			const_iterator
			_lower_bound( const key_type& key, node_ptr root, node_ptr result ) const
			{
				while (root != 0)
				{
					if (!this->_key_compare(root->content.first, key))
					{
						result = root;
						root = root->left;
					}
					else
						root = root->right;
				}
				return const_iterator(result);
			}

			iterator
			_upper_bound( const key_type& key, node_ptr root, node_ptr result )
			{
				while (root != 0)
				{
					if (this->_key_compare(key, root->content.first))
					{
						result = root;
						root = root->left;
					}
					else
						root = root->right;
				}
				return iterator(result);
			}

			const_iterator
			_upper_bound( const key_type& key, node_ptr root, node_ptr result ) const
			{
				while (root != 0)
				{
					if (this->_key_compare(key, root->content.first))
					{
						result = root;
						root = root->left;
					}
					else
						root = root->right;
				}
				return const_iterator(result);
			}

		public:
			iterator
			lower_bound( const key_type& key )
			{
				return this->_lower_bound(key, this->_root(), this->end();
			}

			const_iterator
			lower_bound( const key_type& key ) const
			{
				return this->_lower_bound(key, this->_root(), this->end();
			}

			iterator
			upper_bound( const key_type& key )
			{
				return this->_upper_bound(key, this->_root(), this->end();
			}

			const_iterator
			upper_bound( const key_type& key ) const
			{
				return this->_upper_bound(key, this->_root(), this->end();
			}

			key_compare
			key_comp( void ) const
			{
				return this->_key_compare;
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
