#ifndef FT_TREE_HPP
# define FT_TREE_HPP

# include "../iterator/tree_iterator.hpp"
# include "../iterator/reverse_iterator.hpp"
# include "../utility/pair.hpp"
# include "../algorithm/equal.hpp"
# include "../algorithm/lexicographical_compare.hpp"
# include "../types/enable_if.hpp"
# include "../types/is_integral.hpp"
/*
# include "tree_iterator.hpp"
# include "reverse_iterator.hpp"
# include "pair.hpp"
# include "equal.hpp"
# include "lexicographical_compare.hpp"
# include "enable_if.hpp"
# include "is_integral.hpp"
*/
# include <iostream>
# include <cstddef>
# include <memory>
# include <algorithm>

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

			node_ptr	parent;
			node_ptr	left;
			node_ptr	right;
			value_type	content;
			tree_color	color;

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
			is_left_child( node_ptr x )
			{
				return x != 0 && x == x->parent->left;
			}

			static bool
			is_right_child( node_ptr x )
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

			static const_node_ptr
			increment( const_node_ptr current )
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

			static const_node_ptr
			decrement( const_node_ptr current )
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

	template< typename Key, typename Type, typename Compare,
			  typename Alloc = std::allocator<Type> >
		class	tree
		{
		public:
			typedef Key												key_type;
			typedef Type											mapped_type;
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
			tree_node_type	_sentinel;
			key_compare		_key_compare;
			size_type		_node_count;
			node_allocator	_allocator;

			node_ptr
			_get_node( void )
			{
				return this->_allocator.allocate(1);
			}

			void
			_put_node( node_ptr node )
			{
				this->_allocator.deallocate(node, 1);
			}

			void
			_destroy_node( node_ptr node )
			{
				this->_allocator.destroy(node);
				this->_put_node(node);
			}

			node_ptr
			_create_node( const value_type& value )
			{
				node_ptr	node(this->_get_node());

				this->_allocator.construct(node, value);
				return node;
			}

			node_ptr
			_clone_node( const_node_ptr node )
			{
				node_ptr	clone(this->_create_node(node->content));

				clone->color = node->color;
				clone->left = 0;
				clone->right = 0;
				return clone;
			}

			void
			_init_empty_tree( void )
			{
				this->_sentinel.color = red;
				this->_sentinel.parent = 0;
				this->_sentinel.left = &this->_sentinel;
				this->_sentinel.right = &this->_sentinel;
				this->_node_count = 0;
			}

			node_ptr
			_assign_node( const_node_ptr root, node_ptr parent )
			{
				node_ptr	node(this->_clone_node(root));

				node->parent = parent;
				if (root->right)
					node->right = this->_copy_tree(root->right, node);
				return node;
			}

			node_ptr
			_copy_tree( const_node_ptr root, node_ptr parent )
			{
				node_ptr	top;
				node_ptr	leftmost;

				top = this->_assign_node(root, parent);
				parent = top;
				for (root = root->left; root != 0; root = root->left)
				{
					leftmost = this->_assign_node(root, parent);
					parent->left = leftmost;
					parent = leftmost;
				}
				return top;
			}

			node_ptr
			_end( void )
			{
				return &this->_sentinel;
			}

			const_node_ptr
			_end( void ) const
			{
				return &this->_sentinel;
			}

			node_ptr&
			_root( void )
			{
				return this->_sentinel.parent;
			}

			const_node_ptr
			_root( void ) const
			{
				return this->_sentinel.parent;
			}

			node_ptr&
			_leftmost( void )
			{
				return this->_sentinel.left;
			}

			const_node_ptr
			_leftmost( void ) const
			{
				return this->_sentinel.left;
			}

			node_ptr&
			_rightmost( void )
			{
				return this->_sentinel.right;
			}

			const_node_ptr
			_rightmost( void ) const
			{
				return this->_sentinel.right;
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

			void
			_rotate_left( node_ptr const node )
			{
				node_ptr const	child = node->right;

				node->right = child->left;
				if (child->left != 0)
					child->left->parent = node;
				child->parent = node->parent;
				if (node == this->_root())
					this->_sentinel.parent = child;
				else if (node == node->parent->left)
					node->parent->left = child;
				else
					node->parent->right = child;
				child->left = node;
				node->parent = child;
			}

			void
			_rotate_right( node_ptr const node )
			{
				node_ptr const	child = node->left;

				node->left = child->right;
				if (child->right != 0)
					child->right->parent = node;
				child->parent = node->parent;
				if (node == this->_root())
					this->_sentinel.parent = child;
				else if (node == node->parent->right)
					node->parent->right = child;
				else
					node->parent->left = child;
				child->right = node;
				node->parent = child;
			}

			void
			_init_child_node( node_ptr node, node_ptr parent )
			{
				node->parent = parent;
				node->left = 0;
				node->right = 0;
				node->color = red;
			}

			void
			_rebalance_right_uncle( node_ptr& node, node_ptr const& gparent )
			{
				node_ptr const	uncle = gparent->right;

				if (uncle && uncle->color == red)
				{
					node->parent->color = black;
					uncle->color = black;
					gparent->color = red;
					node = gparent;
				}
				else
				{
					if (node == node->parent->right)
					{
						node = node->parent;
						this->_rotate_left(node);
					}
					node->parent->color = black;
					gparent->color = red;
					this->_rotate_right(gparent);
				}
			}

			void
			_rebalance_left_uncle( node_ptr& node, node_ptr const& gparent )
			{
				node_ptr const	uncle = gparent->left;

				if (uncle && uncle->color == red)
				{
					node->parent->color = black;
					uncle->color = black;
					gparent->color = red;
					node = gparent;
				}
				else
				{
					if (node == node->parent->left)
					{
						node = node->parent;
						this->_rotate_right(node);
					}
					node->parent->color = black;
					gparent->color = red;
					this->_rotate_left(gparent);
				}
			}

			void
			_insert_and_rebalance( const bool insert_left,
					node_ptr node, node_ptr parent )
			{
				node_ptr&	root = this->_sentinel.parent;

				this->_init_child_node(node,parent);

				if (insert_left)
				{
					parent->left = node;
					if (parent == &this->_sentinel)
					{
						this->_root() = node;
						this->_rightmost() = node;
					}
					else if (parent == this->_leftmost())
						this->_leftmost() = node;
				}
				else
				{
					parent->right = node;
					if (parent == this->_rightmost())
						this->_rightmost() = node;
				}
				//rebalance
				while (node != root && node->parent->color == red)
				{
					node_ptr const	gparent = node->parent->parent;

					if (gparent)
					{
						if (gparent->left == node->parent)
							this->_rebalance_right_uncle(node, gparent);
						else
							this->_rebalance_left_uncle(node, gparent);
					}
				}
				root->color = black;
			}

			bool
			_has_both_child( node_ptr current, node_ptr& child )
			{
				if (current->left == 0)
					child = current->right;
				else if (current->right == 0)
					child = current->left;
				else
					return true;
				return false;
			}

			void
			_relink_child_parent( node_ptr& parent, node_ptr& child,
					node_ptr& current, node_ptr& node )
			{
				if (current != node->right)
				{
					parent = current->parent;
					if (child)
						child->parent = parent;
					current->parent->left = child;
					current->right = node->right;
					node->right->parent = current;
				}
				else
					parent = current;
			}

			void
			_relink_left_and_rightmost_node( node_ptr node, node_ptr child )
			{
				if (this->_leftmost() == node)
				{
					if (node->right == 0)
						this->_leftmost() = node->parent;
					else
						this->_leftmost() = tree::_minimum(child);
				}
				if (this->_rightmost() == node)
				{
					if (node->left == 0)
						this->_rightmost() = node->parent;
					else
						this->_rightmost() = tree::_maximum(child);
				}
			}

			void
			_replace_node( node_ptr node, node_ptr& current,
					node_ptr& child, node_ptr& parent )
			{
				if (this->_has_both_child(current, child))
				{
					current = tree::_minimum(node->right);
					child = current->right;
					node->left->parent = current;
					current->left = node->left;
					this->_relink_child_parent(parent, child, current, node);
					if (this->_root() == node)
						this->_root() = current;
					else if (node->parent->left == node)
						node->parent->left = current;
					else
						node->parent->right = current;
					current->parent = node->parent;
					std::swap(current->color, node->color);
				}
				else
				{
					parent = node->parent;
					if (child)
						child->parent = parent;
					if (this->_root() == node)
						this->_root() = child;
					else if (node->parent->left == node)
						node->parent->left = child;
					else
						node->parent->right = child;
					this->_relink_left_and_rightmost_node(node, child);
				}
			}

			bool
			_is_node_black( node_ptr node )
			{
				return node == 0 || node->color == black;
			}

			bool
			_are_both_child_black( node_ptr node )
			{
				return this->_is_node_black(node->left)
						&& this->_is_node_black(node->right);
			}

			bool
			_rebalance_from_right_sibling( node_ptr& child, node_ptr& parent )
			{
				node_ptr	sibling = parent->right;

				if (sibling->color == red)
				{
					sibling->color = black;
					parent->color = red;
					this->_rotate_left(parent);
				}
				if (this->_are_both_child_black(sibling))
				{
					sibling->color = red;
					child = parent;
					parent = parent->parent;
				}
				else
				{
					if (this->_is_node_black(sibling->right))
					{
						sibling->left->color = black;
						sibling->color = red;
						this->_rotate_right(sibling);
						sibling = parent->right;
					}
					sibling->color = parent->color;
					parent->color = black;
					if (sibling->right)
						sibling->right->color = black;
					this->_rotate_left(parent);
					return true;
				}
				return false;
			}

			bool
			_rebalance_from_left_sibling( node_ptr& child, node_ptr& parent )
			{
				node_ptr	sibling = parent->left;

				if (sibling->color == red)
				{
					sibling->color = black;
					parent->color = red;
					this->_rotate_right(parent);
				}
				if (this->_are_both_child_black(sibling))
				{
					sibling->color = red;
					child = parent;
					parent = parent->parent;
				}
				else
				{
					if (this->_is_node_black(sibling->left))
					{
						sibling->right->color = black;
						sibling->color = red;
						this->_rotate_left(sibling);
						sibling = parent->left;
					}
					sibling->color = parent->color;
					parent->color = black;
					if (sibling->left)
						sibling->left->color = black;
					this->_rotate_right(parent);
					return true;
				}
				return false;
			}

			void
			_rebalance_before_erase( node_ptr node )
			{
				node_ptr	current(node);
				node_ptr	child(0);
				node_ptr	parent(0);

				this->_replace_node(node, current, child, parent);
				if (node->color != red)
				{
					while (child != this->_root()
							&& (child == 0 || child->color == black))
					{
						if (child == parent->left)
						{
							if (parent->right == 0
									|| this->_rebalance_from_right_sibling(child, parent))
								break ;
						}
						else
						{
							if (this->_rebalance_from_left_sibling(child, parent))
								break ;
						}
					}
					if (child)
						child->color = black;
				}
			}

			void
			_copy_sentinel_and_count( const tree<key_type, mapped_type,
					key_compare, allocator_type>& other )
			{
				this->_sentinel.parent = this->_copy_tree(other._root(), &this->_sentinel);
				this->_sentinel.left = tree::_minimum(this->_root());
				this->_sentinel.right = tree::_maximum(this->_root());
				this->_node_count = other._node_count;
			}

		public:
			/*	default constructor	*/
			tree( void )
			: _key_compare()
			, _allocator()
			{
				this->_init_empty_tree();
			}

			tree( const Compare& comp)
			: _key_compare(comp)
			, _allocator()
			{
				this->_init_empty_tree();
			}

			tree( const Compare& comp, const allocator_type& a )
			: _key_compare(comp)
			, _allocator(a)
			{
				this->_init_empty_tree();
			}

			tree( const tree<key_type, mapped_type, key_compare, allocator_type>& other )
			: _key_compare(other._key_compare)
			, _allocator(other._allocator)
			{
				this->_init_empty_tree();
				if (!other.empty())
					this->_copy_sentinel_and_count(other);
			}

			~tree( void )
			{
				this->_erase_tree(this->_root());
			}

			const tree<key_type, mapped_type, key_compare, allocator_type>&
			operator=( const tree<key_type, mapped_type, key_compare, allocator_type>& rhs)
			{
				if (this != &rhs)
				{
					this->clear();
					this->_key_compare = rhs._key_compare;
					this->_allocator = rhs._allocator;
					if (!rhs.empty())
						this->_copy_sentinel_and_count(rhs);
				}
				return *this;
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
				return iterator(&this->_sentinel);
			}

			const_iterator
			end( void ) const
			{
				return const_iterator(&this->_sentinel);
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
			size( void ) const
			{
				return this->_node_count;
			}

			size_type
			max_size( void ) const
			{
				return this->_allocator.max_size();
			}

		protected:
			void
			_erase_tree( node_ptr current )
			{
				node_ptr	left;

				while (current != 0)
				{
					this->_erase_tree(current->right);
					left = current->left;
					this->_destroy_node(current);
					current = left;
				}
			}

		public:
			void
			clear( void )
			{
				this->_erase_tree(this->_root());
				this->_init_empty_tree();
			}

		protected:
			static const key_type&
			_key( const_node_ptr x )
			{
				return x->content.first;
			}

			iterator
			_insert( node_ptr pos, node_ptr parent,
					const value_type& value )
			{
				bool		insert_left = (pos != 0 || parent == this->_end()
										|| this->_key_compare(value.first, tree::_key(parent)));

				node_ptr	node = this->_create_node(value);

				this->_insert_and_rebalance(insert_left, node, parent);
				++this->_node_count;
				return iterator(node);
			}

			iterator
			_insert_before_position( iterator position, const value_type& value )
			{
				if (position.node == this->_leftmost())
					return this->_insert(this->_leftmost(), this->_leftmost(), value);
				return (this->insert(value).first);
			}

			iterator
			_insert_after_position( iterator position, const value_type& value )
			{
				if (position.node == this->_rightmost())
					return this->_insert(0, this->_rightmost(), value);
				return (this->insert(value)).first;
			}

			iterator
			_insert_last_position( const value_type& value )
			{
				if (this->size() > 0
						&& this->_key_compare(tree::_key(this->_rightmost()), value.first))
					return this->_insert(0, this->_rightmost(), value);
				return (this->insert(value)).first;
			}

		public:
			ft::pair<iterator, bool>
			insert( const value_type& value )
			{
				typedef ft::pair<iterator, bool>	pair_type;

				node_ptr	pos = this->_root();
				node_ptr	parent = this->_end();

				while (pos != 0)
				{
					parent = pos;
					if (this->_key_compare(value.first, tree::_key(pos)))
						pos = pos->left;
					else if (this->_key_compare(tree::_key(pos), value.first))
						pos = pos->right;
					else
						return pair_type(iterator(pos), false);
				}
				return pair_type(this->_insert(pos, parent, value), true);
			}

			iterator
			insert( iterator position, const value_type& value )
			{
				if (position == this->end())
					return this->_insert_last_position(value);
				else if (this->_key_compare(value.first, tree::_key(position.node)))
					return this->_insert_before_position(position, value);
				else if (this->_key_compare(tree::_key(position.node), value.first))
					return this->_insert_after_position(position, value);
				return position;
			}

			template< typename InputIterator >
				void
				insert( typename ft::enable_if<
						!ft::is_integral<InputIterator>::value, InputIterator>::type first,
						InputIterator last)
				{
					for (; first != last; ++first)
						this->insert(this->end(), *first);
					//debug
//					this->debug();
				}

			void
			erase( iterator position )
			{
				this->_rebalance_before_erase(position.node);
				this->_destroy_node(position.node);
				--this->_node_count;
				//debug
//				this->debug();
			}

			size_type
			erase( const key_type& key )
			{
				iterator	position;

				position = this->find(key);
				if (position == this->end())
					return 0;
				this->erase(position);
				return 1;
			}

			void
			erase( iterator first, iterator last )
			{
				if (first == this->begin() && last == this->end())
					this->clear();
				else
				{
					while (first != last)
						this->erase(first++);
				}
			}

			void
			swap( tree<key_type, mapped_type, key_compare, allocator_type>& other )
			{
				if (this->_root() == 0)
				{
					if (other._root() != 0)
					{
						this->_root() = other._root();
						this->_leftmost() = other._leftmost();
						this->_rightmost() = other._rightmost();
						this->_root()->parent = this->_end();
						other._root() = 0;
						other._leftmost() = other._end();
						other._rightmost() = other._end();
					}
					else
					{
						other._root() = this->_root();
						other._leftmost() = this->_leftmost();
						other._rightmost() = this->_rightmost();
						other._root()->parent = other._end();
						this->_root() = 0;
						this->_leftmost() = this->_end();
						this->_rightmost() = this->_end();
					}
				}
				else
				{
					std::swap(this->_root(), other._root());
					std::swap(this->_leftmost(), other._leftmost());
					std::swap(this->_rightmost(), other._rightmost());
					this->_root()->parent = this->_end();
					other._root()->parent = other._end();
				}
				std::swap(this->_node_count, other._node_count);
				std::swap(this->_key_compare, other._key_compare);
				std::swap(this->_allocator, other._allocator);
			}

			size_type
			count( const key_type& key ) const
			{
				const_node_ptr	x = this->_root();

				while (x != 0)
				{
					if (this->_key_compare(key, tree::_key(x)))
						x = x->left;
					else if (this->_key_compare(tree::_key(x), key))
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
					if (!this->_key_compare(tree::_key(x), key))
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
					if (!this->_key_compare(tree::_key(x), key))
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
			_upper_bound( const key_type& key, node_ptr x, node_ptr result )
			{
				while (x != 0)
				{
					if (this->_key_compare(key, tree::_key(x)))
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
					if (this->_key_compare(key, tree::_key(x)))
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
				iterator	position(this->_lower_bound(key, this->_root(), this->_end()));

				if (position != this->end() && !this->_key_compare(key, position->first))
					return position;
				return this->end();
			}

			const_iterator
			find( const key_type& key ) const
			{
				const_iterator	position(this->_lower_bound(key, this->_root(), this->_end()));

				if (position != this->end() && !this->_key_compare(key, position->first))
					return position;
				return this->end();
			}

			ft::pair<iterator, iterator>
			equal_range( const key_type& key )
			{
				typedef ft::pair<iterator, iterator>	pair_type;

				node_ptr	x = this->_root();
				node_ptr	result = this->_end();

				while (x != 0)
				{
					if (this->_key_compare(key, tree::_key(x)))
					{
						result = x;
						x = x->left;
					}
					else if (this->_key_compare(tree::_key(x), key))
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
				const_node_ptr	result = this->_end();

				while (x != 0)
				{
					if (this->_key_compare(key, tree::_key(x)))
					{
						result = x;
						x = x->left;
					}
					else if (this->_key_compare(tree::_key(x), key))
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
				return this->_lower_bound(key, this->_root(), this->_end());
			}

			const_iterator
			lower_bound( const key_type& key ) const
			{
				return this->_lower_bound(key, this->_root(), this->_end());
			}

			iterator
			upper_bound( const key_type& key )
			{
				return this->_upper_bound(key, this->_root(), this->_end());
			}

			const_iterator
			upper_bound( const key_type& key ) const
			{
				return this->_upper_bound(key, this->_root(), this->_end());
			}

			key_compare
			key_comp( void ) const
			{
				return this->_key_compare;
			}

			void
			debug( void )
			{
				node_ptr	current = this->_leftmost();
				size_type	elems = this->_node_count;

				std::cout << "-----------------------" << std::endl;
				std::cout << "##tree elems##" << std::endl;
				std::cout << "-----------------------" << std::endl;
				std::cout << "sentinel_node = " << &this->_sentinel << std::endl;
				std::cout << "root_node = " << this->_root() << std::endl;
				std::cout << "leftmost_node = " << this->_leftmost() << std::endl;
				std::cout << "rightmost_node = " << this->_rightmost() << std::endl;
				std::cout << "-----------------------" << std::endl;
				std::cout << "begin = " << &(*this->begin()) << std::endl;
				std::cout << "end = " << &(*this->end()) << std::endl;
				std::cout << "-----------------------" << std::endl;
				std::cout << "total nodes = " << this->_node_count << std::endl;
				std::cout << "-----------------------" << std::endl;
				while (elems != 0)
				{
					if (current->parent == &this->_sentinel)
						std::cout << "ROOT NODE" << std::endl;
					std::cout << "node = " << current << std::endl;
					std::cout << "content: first = " << current->content.first << std::endl;
					std::cout << "	second = " << current->content.second << std::endl;
					std::cout << "color = ";
					std::cout << ((current->color == red) ? "red" : "black") << std::endl;
					std::cout << "parent = " << current->parent << std::endl;
					std::cout << "right = " << current->right << std::endl;
					std::cout << "left = " << current->left << std::endl;
					std::cout << "-----------------------" << std::endl;
					current = _increment(current);
					--elems;
				}
				std::cout << std::endl;
				graph_display(this->_root());
			}

			void
			graph_display( const node_ptr node, const std::string& prefix = "", bool left = false )
			{
				if (node != 0)
				{
					std::cout << prefix << (left ? "?????????" : "?????????") << tree::_key(node);
					std::cout << ": " << ((node->color == red) ? "r" : "b") << std::endl;

					graph_display(node->left, prefix + (left ? "???   " : "    "), true);
					graph_display(node->right, prefix + (left ? "???   " : "    "), false);
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
