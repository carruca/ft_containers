#ifndef FT_ITERATORS_TRAITS_HPP
# define FT_ITERATORS_TRAITS_HPP

# include <cstddef>

namespace	ft
{
	template< typename Iterator >
	struct	iterator_traits
	{
		typedef	typename Iterator::difference_type			difference_type;
		typedef typename Iterator::value_type				value_type;
		typedef typename Iterator::pointer					pointer;
		typedef typename Iterator::reference				reference;
		typedef typename Iterator::iterator_category		iterator_category;
	};

	template< typename T >
	struct	iterator_traits<T*>
	{
		typedef	typename std::ptrdiff_t						difference_type;
		typedef typename T									value_type;
		typedef typename T*									pointer;
		typedef typename T&									reference;
		typedef typename std::random_access_iterator_tag	iterator_category;
	};

	template< typename T >
	struct	iterator_traits<const T*>
	{
		typedef	typename std::ptrdiff_t						difference_type;
		typedef typename T									value_type;
		typedef typename const T*							pointer;
		typedef typename const T&							reference;
		typedef typename std::random_access_iterator_tag	iterator_category;
	};
};

#endif
