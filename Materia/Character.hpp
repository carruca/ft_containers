#ifndef CHARACTER_HPP
# define CHARACTER_HPP

# include <iostream>
# include <string>
# include "ICharacter.hpp"

class	Character : public ICharacter {

protected:

	AMateria			*inventory[4];
	std::string			name;

public:

	Character( void );
	Character( std::string const &name );
	Character( Character const &src );
	~Character( void );

	Character	&operator=( Character const &rhs );

	std::string const	&getName( void ) const;

	void				equip( AMateria *m );
	void				unequip( int idx );
	void				use( int idx, ICharacter &target );
};

#endif
