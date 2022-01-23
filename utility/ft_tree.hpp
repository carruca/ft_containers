#ifndef FT_TREE_HPP
# define FT_TREE_HPP

# include <cstddef>
# include <memory>

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
		};

	template< typename Key, typename Value, typename Compare,
			  typename Alloc = std::allocator<Value> >
		class	tree
		{
		public:
			typedef Key						key_type;
			typedef Value					value_type;
			typedef std::size_t				size_type;
			typedef	Alloc					allocator_type;

			/*	default constructor	*/
			tree( void )
			{
			}

			tree( const Compare& comp)
			: _comp(comp),
			, _node_count(0)
			{
			}

			tree( const Compare& comp, const allocator_type& a )
			: _comp(comp)
			, _node_count(0)
			, allocator(a)
			{}

			tree( const tree<Key, Value, Compare, Alloc>& x )
			{	
			}

			~tree( void )
			{
				//erase
			}

			const tree<Key, Value, Compare, Alloc>&
			operator=( const tree<Key, value, Compare, Alloc>& rhs)
			{
			}

		protected:
			typedef tree_node<value_type>	tree_node_type;
			typedef tree_node_type*			node_ptr;
			typedef const tree_node_type*	const_node_ptr;

			Compare		_comp;
			tree_node	_header;
			size_type	_node_count;
			Alloc		_allocator;
/*
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
*/
			node_ptr
			_minimum( node_ptr x )
			{
				while (x->left != 0)
					x = x->left;
				return x;
			}

			const_node_ptr
			_minimum( node_ptr x )
			{
				while (x->left != 0)
					x = x->left;
				return x;
			}

			node_ptr
			_maximum( node_ptr x )
			{
				while (x->right != 0)
					x = x->right;
				return x;
			}

			const_node_ptr
			_maximum( node_ptr x )
			{
				while (x->right != 0)
					x = x->right;
				return x;
			}

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
		};
}

#endif
