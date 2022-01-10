#include "AMateria.hpp"

AMateria::AMateria( void ) : type( "materia" ){

	std::cout << "Default AMateria constructor called" << std::endl;
	return ;
}

AMateria::AMateria( std::string const &type ) : type( type ) {

	std::cout << "Parameter AMateria constructor called" << std::endl;
	return ;
}

AMateria::AMateria( AMateria const &src ) : type( src.getType() ) {

	*this = src;
	std::cout << "Copy AMateria constructor called" << std::endl;
	return ;
}

AMateria::~AMateria( void ) {

	std::cout << "Default AMateria destructor called" << std::endl;
	return ;
}

AMateria	&AMateria::operator=( AMateria const &rhs ) {

	if (this == &rhs)
		return *this;
	this->type = rhs.getType();
	std::cout << "Assignment AMateria operator called" << std::endl;
	return *this;
}

std::string const	&AMateria::getType( void ) const {

	return this->type;
}

void	AMateria::use( ICharacter &target ) {

	std::cout << "* uses some " << this->type << " against " << target.getName() << " *" << std::endl;
	return ;
}
