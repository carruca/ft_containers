#include "Character.hpp"
#include <cstring>

Character::Character( void ) : name( "Default" ) {

	std::cout << "Default Character constructor called" << std::endl;
	std::memset( this->inventory, 0, sizeof(AMateria *) * 4 );
	return ;
}

Character::Character( std::string const &name ) : name( name ) {

	std::cout << "Parameter Character constructor called" << std::endl;
	std::memset( this->inventory, 0, sizeof(AMateria *) * 4 );
	return ;
}

Character::Character( Character const &src ) : name( src.getName() ) {

	std::cout << "Copy Character constructor called" << std::endl;
	for (int i = 0; i < 4; i++)
		this->inventory[i] = src.inventory[i]->clone();
	*this = src;
	return ;
}

Character::~Character( void ) {

	std::cout << "Default Character destructor called" << std::endl;
	for (int i = 0; i < 4; i++) {

		if (this->inventory[i])
			delete this->inventory[i];
	}
	return ;
}

Character	&Character::operator=( Character const &rhs ) {

	std::cout << "Assignment AMateria operator called" << std::endl;
	if (this == &rhs)
		return *this;
	this->name = rhs.getName();
	for (int i = 0; i < 4; i++) {

		if (this->inventory[i])
			delete this->inventory[i];
		this->inventory[i] = rhs.inventory[i]->clone();
	}
	return *this;
}

std::string const	&Character::getName( void ) const {

	return this->name;
}

void	Character::equip( AMateria *m ) {

	for (int i = 0; i < 4; i++) {

		if (!this->inventory[i]) {

			this->inventory[i] = m;
			break;
		}
	}
	return ;
}

void	Character::unequip( int idx ) {

	if ( idx < 4 && idx >= 0 && this->inventory[idx] )
		this->inventory[idx] = NULL;
	return ;
}

void	Character::use( int idx, ICharacter &target ) {

	if ( idx < 4 && idx >= 0 && this->inventory[idx])
		this->inventory[idx]->use( target );
	return ;
}
