#ifndef FT_REVERSE_ITERATOR_HPP
# define FT_REVERSE_ITERATOR_HPP

namespace	ft
{	
	template< typename Iterator >
	class	reverse_iterator
	: public std::iterator< ft::iterator_traits<Iterator>::iterator_category,
							ft::iterator_traits<Iterator>::value_type,
							ft::iterator_traits<Iterator>::difference_categpry,
							ft::iterator_traits<Iterator>::pointer,
							ft::iterator_traits<Iterator>::reference >
	{
	public:
		typedef typename Iterator											iterator_type;
		typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
		typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
		typedef typename ft::iterator_traits<Iterator>::difference_category	difference_category;
		typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
		typedef typename ft::iterator_traits<Iterator>::reference			reference;	

		/*	default constructor	*/
		reverse_iterator( void ) {};

	};
};

#endif
