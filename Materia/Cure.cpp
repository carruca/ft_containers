#include "Cure.hpp"

Cure::Cure( void ) : AMateria( "cure" ) {

	std::cout << "Default Cure constructor called" << std::endl;
	return ;
}

Cure::Cure( Cure const &src ) : AMateria( src.getType() ) {

	*this = src;
	std::cout << "Copy Cure constructor called" << std::endl;
	return ;
}

Cure::~Cure( void ) {

	std::cout << "Default Cure destructor called" << std::endl;
	return ;
}

Cure	&Cure::operator=( Cure const &rhs ) {

	std::cout << "Assignment Cure operator called" << std::endl;
	if (this == &rhs)
		return *this;
	this->AMateria::type = rhs.getType();
	return *this;
}

AMateria	*Cure::clone( void ) const {

	AMateria	*clone = new Cure();

	return clone;
}

void	Cure::use( ICharacter &target ) {

	std::cout << "* heals "<< target.getName() << "'s wounds *" << std::endl;
	return ;
}
