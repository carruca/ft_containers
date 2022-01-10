#include "MateriaSource.hpp"
#include <cstring>

MateriaSource::MateriaSource( void ) {

	std::cout << "Default MateriaSource constructor called" << std::endl;
	std::memset( this->source, 0, sizeof(AMateria *) * 4 );
	return ;
}

MateriaSource::MateriaSource( MateriaSource const &src ) {

	std::cout << "Copy MateriaSource constructor called" << std::endl;
	for (int i = 0; i < 4; i++)
			this->source[i] = src.source[i]->clone();
	*this = src;
	return ;
}

MateriaSource::~MateriaSource( void ) {

	std::cout << "Default MateriaSource destructor called" << std::endl;
	for (int i = 0; i < 4; i++) {

		if (this->source[i])
			delete this->source[i];
	}
	return ;
}

MateriaSource	&MateriaSource::operator=( MateriaSource const &rhs ) {

	std::cout << "Assignment AMateria operator called" << std::endl;
	if (this == &rhs)
		return *this;
	for (int i = 0; i < 4; i++) {

		if (this->source[i])
			delete this->source[i];
		this->source[i] = rhs.source[i]->clone();
	}
	return *this;
}

void	MateriaSource::learnMateria( AMateria *src ) {

	std::cout << "New materia learned" << std::endl;
	for (int i = 0; i < 4; i++) {

		if (!this->source[i]) {

			this->source[i] = src;
			break ;
		}
	}
	return ;
}

AMateria	*MateriaSource::createMateria( std::string const &type ) {

	std::cout << type << " materia created" << std::endl;
	for (int i = 0; i < 4; i++) {

		if (this->source[i] && this->source[i]->getType() == type)
			return this->source[i]->clone();
	}
	return NULL;
}
