#ifndef FT_TREE_HPP
# define FT_TREE_HPP

# include <iostream>
# include <cstddef>
# include <memory>
# include <algorithm>
# include "ft_tree_iterator.hpp"
# include "ft_reverse_iterator.hpp"
# include "ft_pair.hpp"
# include "ft_equal.hpp"
# include "ft_lexicographical_compare.hpp"

namespace	ft
{
	enum	tree_color
	{
		red = false,
		black = true
	};

	template< typename T >
		struct	tree_node
		{
			typedef T					value_type;
			typedef struct tree_node	node_type;
			typedef node_type*			node_ptr;
			typedef const node_type*	const_node_ptr;

			tree_color	color;
			node_ptr	parent;
			node_ptr	left;
			node_ptr	right;
			value_type	content;

			tree_node( void )
			{}

			tree_node( const value_type& v )
			: content(v)
			{}

			~tree_node( void )
			{}

			static node_ptr
			minimum( node_ptr x )
			{
				while (x->left != 0)
					x = x->left;
				return x;
			}

			static const_node_ptr
			minimum( const_node_ptr x )
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
			maximum( const_node_ptr x )
			{
				while (x->right != 0)
					x = x->right;
				return x;
			}

			static bool
			is_left_sibling( node_ptr x )
			{
				return x != 0 && x == x->parent->left;
			}

			static bool
			is_right_sibling( node_ptr x )
			{
				return x != 0 && x == x->parent->right;
			}

			static node_ptr
			increment( node_ptr current )
			{
				node_ptr	parent;

				if (current->right != 0)
					return minimum(current->right);
				parent = current->parent;
				while (current == parent->right)
				{
					current = parent;
					parent = current->parent;
				}
				if (current->right != parent)
					current = parent;
				return current;
			}

			static node_ptr
			decrement( node_ptr current )
			{
				node_ptr	parent;

				if (current->color == red
						&& current == current->parent->parent)
					return current->right;
				if (current->left != 0)
					return maximum(current->left);
				parent = current->parent;
				while (current == parent->left)
				{
					current = parent;
					parent = current->parent;
				}
				return parent;
			}
		};

	template< typename Key, typename T, typename Compare,
			  typename Alloc = std::allocator<T> >
		class	tree
		{
		public:
			typedef Key												key_type;
			typedef T												mapped_type;
			typedef ft::pair<const key_type, mapped_type>			value_type;
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
			typedef Compare											key_compare;
			typedef	Alloc											allocator_type;
			typedef ft::tree_iterator<value_type>					iterator;
			typedef ft::tree_const_iterator<value_type>				const_iterator;
			typedef ft::reverse_iterator<iterator>					reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;

		private:
			typedef typename allocator_type::template rebind<tree_node_type>::other	node_allocator;

		protected:
			key_compare		_key_compare;
			tree_node_type	_header;
			size_type		_node_count;
			node_allocator	_allocator;

			node_ptr
			_get_node( void )
			{
				return this->_allocator.allocate(1);
			}

			void
			_put_node( node_ptr x )
			{
				this->_allocator.deallocate(x, 1);
			}

			void
			_destroy_node( node_ptr x )
			{
				this->_allocator.destroy(x);
				this->_put_node(x);
			}

			node_ptr
			_create_node( const value_type& value )
			{
				node_ptr	tmp;

				try
				{
					tmp = this->_get_node();
					this->_allocator.construct(tmp, value);
				}
				catch (...)
				{
					this->_put_node(tmp);
					throw ;
				}
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

			void
			_empty_tree_init( void )
			{
				this->_header.color = red;
				this->_header.parent = 0;
				this->_header.left = &this->_header;
				this->_header.right = &this->_header;
			}

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

			static node_ptr
			_minimum( node_ptr x )
			{
				return tree_node_type::minimum(x);
			}

			static const_node_ptr
			_minimum( const_node_ptr x )
			{
				return tree_node_type::minimum(x);
			}

			static node_ptr
			_maximum( node_ptr x )
			{
				return tree_node_type::maximum(x);
			}

			static const_node_ptr
			_maximum( const_node_ptr x )
			{
				return tree_node_type::maximum(x);
			}

			static node_ptr
			_increment( node_ptr x )
			{
				return tree_node_type::increment(x);
			}

			static node_ptr
			_decrement( node_ptr x )
			{
				return tree_node_type::decrement(x);
			}

			static void
			_rotate_left( node_ptr x, node_ptr& root )
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
			_rotate_right( node_ptr x, node_ptr& root )
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

			void
			_insert_and_rebalance(const bool insert_left,
								node_ptr x, node_ptr p)
			{
				node_ptr&	root = this->_header.parent;

				x->parent = p;
				x->left = 0;
				x->right = 0;
				x->color = red;

				if (insert_left)
				{
					p->left = x;
					if (p == &this->_header)
					{
						this->_header.parent = x;
						this->_header.right = x;
					}
					else if (p == this->_header.left)
						this->_header.left = x;
				}
				else
				{
					p->right = x;
					if (p == this->_header.right)
						this->_header.right= x;
				}
				//rebalance
				while (x != root && x->parent->color == red)
				{
					node_ptr const	xpp = x->parent->parent;

					if (xpp && x->parent == xpp->left)
					{
						node_ptr const	y = xpp->right;
						if (y && y->color == red)
						{
							x->parent->color = black;
							y->color = black;
							xpp->color = red;
							x = xpp;
						}
						else
						{
							if (x == x->parent->right)
							{
								x = x->parent;
								tree::_rotate_left(x, root);
							}
							x->parent->color = black;
							xpp->color = red;
							tree::_rotate_right(xpp, root);
						}
					}
					else
					{
						node_ptr const	y = xpp->left;
						if (y && y->color == red)
						{
							x->parent->color = black;
							y->color = black;
							xpp->color = red;
							x = xpp;
						}
						else
						{
							if (x == x->parent->left)
							{
								x = x->parent;
								tree::_rotate_right(x, root);
							}
							x->parent->color = black;
							xpp->color = red;
							tree::_rotate_left(xpp, root);
						}
					}
				}
				root->color = black;
			}

		public:
			/*	default constructor	*/
			tree( void )
			: _node_count(0)
			{
				this->_empty_tree_init();
			}

			tree( const Compare& comp)
			: _key_compare(comp)
			, _node_count(0)
			{
				this->_empty_tree_init();
			}

			tree( const Compare& comp, const allocator_type& a )
			: _key_compare(comp)
			, _node_count(0)
			, _allocator(a)
			{
				this->_empty_tree_init();
			}

			tree( const tree<key_type, mapped_type, key_compare, allocator_type>& x )
			{
				*this = x;
			}

			~tree( void )
			{
				//call erase
			}

			const tree<key_type, mapped_type, key_compare, allocator_type>&
			operator=( const tree<key_type, mapped_type, key_compare, allocator_type>& rhs)
			{
				(void)rhs;
			}

			allocator_type
			get_allocator( void ) const
			{
				return this->_allocator;
			}

			iterator
			begin( void )
			{
				return iterator(this->_leftmost());
			}

			const_iterator
			begin( void ) const
			{
				return const_iterator(this->_leftmost());
			}

			iterator
			end( void )
			{
				return iterator(&this->_header);
			}

			const_iterator
			end( void ) const
			{
				return const_iterator(&this->_header);
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
/*
			void
			clear( void )
			{
			}
*/
		protected:
			static const key_type&
			_key(const_node_ptr x)
			{
				return x->content.first;
			}

			iterator
			_insert( node_ptr x, node_ptr p, const value_type& v )
			{
				bool		insert_left = (x != 0 || p == &this->_header
										|| this->_key_compare(v.first, tree::_key(p)));

				node_ptr	z = this->_create_node(v);

				this->_insert_and_rebalance(insert_left, z, p);
				++this->_node_count;
				return iterator(z);
			}

		public:
			ft::pair<iterator, bool>
			insert( const value_type& value )
			{
				typedef ft::pair<iterator, bool>	pair_type;

				node_ptr	x = this->_root();
				node_ptr	y = &this->_header;

				while (x != 0)
				{
					y = x;
					x = this->_key_compare(value.first, tree::_key(x))
						? x->left : x->right;
				}
				if (y)
					return pair_type(this->_insert(x, y, value), true);
				return pair_type(iterator(x), false);
			}
/*
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
*/
			void
			swap( tree<key_type, mapped_type, key_compare, allocator_type>& x )
			{
				if (this->root() == 0)
				{
					if (x.root() != 0)
					{
						this->_root() = x._root();
						this->_leftmost() = x._leftmost();
						this->_rightmost() = x._rightmost();
						this->_root()->parent = this->end();
						x._root() = 0;
						x._leftmost() = x.end();
						x._rightmost() = x.end();
					}
					else
					{
						x._root() = this->_root();
						x._leftmost() = this->_leftmost();
						x._rightmost() = this->_rightmost();
						x._root()->parent = x.end();
						this->_root() = 0;
						this->_leftmost() = this->end();
						this->_rightmost() = this->end();
					}
				}
				else
				{
					std::swap(this->_root(), x._root());
					std::swap(this->_leftmost(), x._leftmost());
					std::swap(this->_rightmost(), x._rightmost());
					this->_root()->parent = this->end();
					x._root()->parent = x.end();
				}
				std::swap(this->_key_compare, x._key_compare);
				std::swap(this->_node_count, x._node_count);
				std::swap(this->_allocator, x._allocator);
			}

			size_type
			count( const key_type& key ) const
			{
				const_node_ptr	x = this->_root();

				while (x != 0)
				{
					if (this->_key_compare(key, x->content.first))
						x = x->left;
					else if (this->_key_compare(x->content.first, key))
						x = x->right;
					else
						return 1;
				}
				return 0;
			}

		protected:
			iterator
			_lower_bound( const key_type& key, node_ptr x, node_ptr result )
			{
				while (x != 0)
				{
					if (!this->_key_compare(x->content.first, key))
					{
						result = x;
						x = x->left;
					}
					else
						x = x->right;
				}
				return iterator(result);
			}

			const_iterator
			_lower_bound( const key_type& key, const_node_ptr x, const_node_ptr result ) const
			{
				while (x != 0)
				{
					if (!this->_key_compare(x->content.first, key))
					{
						result = x;
						x = x->left;
					}
					else
						x = x->right;
				}
				return const_iterator(result);
			}

			iterator
			_upper_bound( const key_type& key, const_node_ptr x, const_node_ptr result )
			{
				while (x != 0)
				{
					if (this->_key_compare(key, x->content.first))
					{
						result = x;
						x = x->left;
					}
					else
						x = x->right;
				}
				return iterator(result);
			}

			const_iterator
			_upper_bound( const key_type& key, const_node_ptr x, const_node_ptr result ) const
			{
				while (x != 0)
				{
					if (this->_key_compare(key, x->content.first))
					{
						result = x;
						x = x->left;
					}
					else
						x = x->right;
				}
				return const_iterator(result);
			}

		public:
			iterator
			find( const key_type& key )
			{
				iterator	it = this->_lower_bound(key, this->_root(), &this->_header);

				if (it != this->end() && !this->_key_compare(key, it->first))
					return it;
				return this->end();
			}

			const_iterator
			find( const key_type& x ) const
			{
				const_iterator	it = this->_lower_bound(x, this->_root(), this->end());

				if (it != this->end() && !this->_key_compare(x, it->content.first))
					return it;
				return this->end();
			}

			ft::pair<iterator, iterator>
			equal_range( const key_type& key )
			{
				typedef ft::pair<iterator, iterator>	pair_type;

				const_node_ptr	x = this->_root();
				const_node_ptr	result = this->end();

				while (x != 0)
				{
					if (this->_key_compare(key, x->content.first))
					{
						result = x;
						x = x->left;
					}
					else if (this->_key_compare(x->content.first, key))
						x = x->right;
					else
						return pair_type(iterator(x),
								iterator(x->right != 0 ? x->right : result));
				}
				return pair_type(iterator(result), iterator(result));
			}

			ft::pair<const_iterator, const_iterator>
			equal_range( const key_type& key ) const
			{
				typedef ft::pair<const_iterator, const_iterator>	pair_type;

				const_node_ptr	x = this->_root();
				const_node_ptr	result = this->end();

				while (x != 0)
				{
					if (this->_key_compare(key, x->content.first))
					{
						result = x;
						x = x->left;
					}
					else if (this->_key_compare(x->content.first, key))
						x = x->right;
					else
						return pair_type(const_iterator(x),
								const_iterator(x->right != 0 ? x->right : result));
				}
				return pair_type(const_iterator(result), const_iterator(result));
			}

			iterator
			lower_bound( const key_type& key )
			{
				return this->_lower_bound(key, this->_root(), this->end());
			}

			const_iterator
			lower_bound( const key_type& key ) const
			{
				return this->_lower_bound(key, this->_root(), this->end());
			}

			iterator
			upper_bound( const key_type& key )
			{
				return this->_upper_bound(key, this->_root(), this->end());
			}

			const_iterator
			upper_bound( const key_type& key ) const
			{
				return this->_upper_bound(key, this->_root(), this->end());
			}

			key_compare
			key_comp( void ) const
			{
				return this->_key_compare;
			}

		public:
			void
			debug( void )
			{
				node_ptr x = this->_leftmost();
				size_type	elems = this->_node_count;

				std::cout << "-----------------------" << std::endl;
				std::cout << "##tree##" << std::endl;
				std::cout << "sentinel_node = " << &this->_header << std::endl;
				std::cout << "root_node = " << this->_root() << std::endl;
				std::cout << "leftmost_node = " << this->_leftmost() << std::endl;
				std::cout << "rightmost_node = " << this->_rightmost() << std::endl;
				std::cout << "begin = " << &(*this->begin()) << std::endl;
				std::cout << "end = " << &(*this->end()) << std::endl;
				std::cout << "-----------------------" << std::endl;
				while (elems != 0)
				{
					std::cout << "total nodes = " << this->_node_count << std::endl;
					std::cout << "node = " << x << std::endl;
					std::cout << "content: first = " << x->content.first << " second = " << x->content.second << std::endl;
					std::cout << "color = ";
					if (x->color == red)
						std::cout << "red" << std::endl;
					else
						std::cout << "black" << std::endl;
					std::cout << "parent = " << x->parent << std::endl;
					std::cout << "right = " << x->right << std::endl;
					std::cout << "left = " << x->left << std::endl;
					std::cout << "-----------------------" << std::endl;
					x = _increment(x);
					--elems;
				}
			}
		};

	template< typename Key, typename Value, typename Compare, typename Alloc >
		inline bool
		operator==( const tree<Key,Value,Compare,Alloc>& lhs,
					const tree<Key,Value,Compare,Alloc>& rhs )
		{
			return lhs.size() == rhs.size()
				&& ft::equal(lhs.begin(), lhs.end(), rhs.begin());
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
