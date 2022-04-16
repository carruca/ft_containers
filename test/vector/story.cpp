#include "vector.hpp"

#include <iostream>
#include <algorithm>
#include <vector>
#include <stdexcept>
#include <list>

void	display_weapon(Weapon* weapon)
{
	std::cout << "Weapon of type " << weapon->getType() << std::endl;
}

class	Weapon
{
public:
	Weapon(std::string& type)
	: _type(type)
	{
		std::cout << "Weapon of type " << this->_type << " created" << std::endl;
	}
	~Weapon(void)
	{
		std::cout << "Weapon of type " this->_type << " destroyed" << std::endl;
	}

	const std::string&	getType(void) const
	{
		return this->_type;
	}

private:
	std::string		_type;

	Weapon(void);
	Weapon(const Weapon& other);
	const Warrior&	operator=(const Warrior& rhs);
};

class	Warrior
{
public:
	Warrior(void)
	{
		std::cout << "I became a Warrior in this battle" << std::endl;
		std::cout << "I have " << this->_invt.size();
		std::cout << " weapons in my inventory now." << std::enl;
	}
	Warrior(const Warrior& other)
	{
		this->_invt = other._invt;
	}
	~Warrior(void)
	{
		std::cout << "I died." << std::endl;
	}

	const Warrior&	operator=(const Warrior& rhs)
	{
		if (this != &other)
			this->_invt = other._invt;
		return *this;
	}

	void	equipWeapon(std::size_t n, Weapon* value)
	{
		this->_invt.assign(n, value);
		std::cout << "I equiped my inventory with " << this->_invt.size();
		std::cout << " new weapons of type " << this->getType() << "." << std::endl;
	}

	void	equipWeapon(std::size_t n, NAMESPACE::vector<Weapon *>& value_vector)
	{
		this->_invt.assign(std::size_t n, value_vector.begin(), value_vector.end();
		std::cout << "I equiped my inventory with:" << std::endl;
		for_each(this->_invt.begin(), this->_invt.end(), display_weapon);
	}

private:
	std::string&				_name;
	NAMESPACE::vector<Weapon *>	_invt;
};


void	episode_one(void)
{
	Character	jim;
}
