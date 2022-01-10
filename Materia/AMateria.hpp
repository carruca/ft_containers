#ifndef AMATERIA_HPP
# define AMATERIA_HPP

# include <iostream>
# include <string>
# include "ICharacter.hpp"

class ICharacter;

class	AMateria {

protected:

	std::string		type;

public:

	AMateria( void );
	AMateria( std::string const &type );
	AMateria( AMateria const &src );
	virtual ~AMateria( void );

	AMateria	&operator=( AMateria const &rhs );

	std::string const	&getType( void ) const;

	virtual AMateria	*clone( void ) const = 0;
	virtual void		use( ICharacter &target );
};

#endif
