#ifndef FT_TREE_ITERATOR
# define FT_TREE_ITERATOR

# include <iterator>
# include <cstddef>
# include "ft_iterators_traits.hpp"
# include "ft_tree.hpp"

namespace	ft
{
	template< typename T >
		struct	tree_node;

	template< typename T >
		struct	tree_iterator
		{
			typedef T								value_type;
			typedef value_type&						reference;
			typedef value_type*						pointer;
			typedef std::bidirectional_iterator_tag	iterator_category;
			typedef std::ptrdiff_t					difference_type;
			typedef ft::tree_node<value_type>		tree_node_type;
			typedef tree_node_type*					node_ptr;
			typedef tree_iterator<value_type>		self;

			tree_iterator( void )
			: node()
			{}

			explicit
			tree_iterator( const node_ptr x )
			: node(x)
			{}

			reference
			operator*( void ) const
			{
				return this->node->content;
			}

			pointer
			operator->( void ) const
			{
				return &this->node->content;
			}

			self&
			operator++( void )
			{
				this->node = tree_node_type::increment(node);
				return *this;
			}

			self&
			operator--( void )
			{
				this->node = tree_node_type::decrement(node);
				return *this;
			}

			self
			operator++( int )
			{
				self	tmp = *this;

				this->node = tree_node_type::increment(node);
				return tmp;
			}

			self
			operator--( int )
			{
				self	tmp = *this;

				this->node = tree_node_type::decrement(node);
				return tmp;
			}

			bool
			operator==( const self& x ) const
			{
				return this->node == x.node;
			}

			bool
			operator!=( const self& x ) const
			{
				return this->node != x.node;
			}

			node_ptr	node;
		};

	template< typename T >
		struct	tree_const_iterator
		{
			typedef T								value_type;
			typedef const value_type&				reference;
			typedef const value_type*				pointer;
			typedef ft::tree_iterator<value_type>	iterator;
			typedef std::bidirectional_iterator_tag	iterator_category;
			typedef std::ptrdiff_t					difference_type;
			typedef ft::tree_node<value_type>		tree_node_type;
			typedef const tree_node_type*			node_ptr;
			typedef tree_iterator<value_type>		self;

			tree_const_iterator( void )
			: node()
			{}

			explicit
			tree_const_iterator( const node_ptr x )
			: node(x)
			{}

			tree_const_iterator( const iterator& iterator )
			: node(iterator.node)
			{}

			reference
			operator*( void ) const
			{
				return this->node->content;
			}

			pointer
			operator->( void ) const
			{
				return &this->node->content;
			}

			self&
			operator++( void )
			{
				this->node = tree_node_type::increment(node);
				return *this;
			}

			self&
			operator--( void )
			{
				this->node = tree_node_type::decrement(node);
				return *this;
			}

			self
			operator++( int )
			{
				self	tmp = *this;

				this->node = tree_node_type::increment(node);
				return tmp;
			}

			self
			operator--( int )
			{
				self	tmp = *this;

				this->node = tree_node_type::decrement(node);
				return tmp;
			}

			bool
			operator==( const self& x ) const
			{
				return this->node == x.node;
			}

			bool
			operator!=( const self& x ) const
			{
				return this->node != x.node;
			}

			node_ptr	node;
		};

	template< typename T >
		inline bool
		operator==( const tree_iterator<T>& lhs,
					const tree_iterator<T>& rhs )
		{
			return lhs.node == rhs.node;
		}

	template< typename T >
		inline bool
		operator!=( const tree_iterator<T>& lhs,
					const tree_iterator<T>& rhs )
		{
			return lhs.node != rhs.node;
		}
}

#endif
