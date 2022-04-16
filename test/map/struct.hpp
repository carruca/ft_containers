#ifndef MAP_STRUCT_HPP
# define MAP_STRUCT_HPP

# include "global.hpp"
# include "map.hpp"

# include <map>

typedef NAMESPACE::map<int, std::string>						map_type;
typedef map_type::iterator										map_iterator;
typedef map_type::const_iterator								map_const_iterator;

typedef NAMESPACE::map<int, int>								intMap_type;
typedef intMap_type::iterator									intMap_iterator;
typedef intMap_type::const_iterator								intMap_const_iterator;

typedef NAMESPACE::pair<int,int>								intPair_type;

typedef NAMESPACE::pair<map_iterator, map_iterator>				pair_type;
typedef NAMESPACE::pair<map_const_iterator, map_const_iterator>	pair_const_type;

#endif
