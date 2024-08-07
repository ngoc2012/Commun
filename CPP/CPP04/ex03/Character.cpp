/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/02 11:51:25 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Character.hpp"

Character::Character()
{
	for (int i = 0; i < SLOTS; i++) {slots[i] = 0;}
	std::cout << "Character default constructor." << std::endl;
}
Character::Character(std::string const &_name)
{
	for (int i = 0; i < SLOTS; i++) {slots[i] = 0;}
	name = _name;
	std::cout << "Character constructor avec string as parameter." << std::endl;
}
Character::Character(const Character& src) {
	*this = src;
	std::cout << "Character copy constructor." << std::endl;
}
void	Character::destroy(void)
{
	for (int i = 0; i < SLOTS; i++)
		if (slots[i])
		{
			std::cout << "Destroy character " << slots[i]->getType() << " at slot " << i << std::endl;
			delete slots[i];
		}
}
Character&	Character::operator=( Character const & src )
{
	destroy();
	for (int i = 0; i < SLOTS; i++)
		slots[i] = src.slots[i]->clone();
	return (*this);
}
Character::~Character()
{
	destroy();
 	std::cout << "Character destructor." << std::endl;
}
std::string const	&Character::getName(void) const {return (name);}

void	Character::equip(AMateria* m)
{
	int	i = -1;
	while (++i < SLOTS && slots[i])
		if (slots[i] == m)
		{
			std::cerr << "ERROR: Materia " << m->getType() << " does existed in this character." << std::endl;
			return ;
		}
	if (i == SLOTS)
	{
		std::cerr << "ERROR: Character slots are full." << std::endl;
		return ;
	}
	std::cout << "Slot " << i << " is equiped with " << m->getType() << std::endl;
	slots[i] = m;
}

void	Character::unequip(int idx)
{
	if (idx < 0 || idx >= SLOTS)
		std::cerr << "ERROR Unequip: Indice slot " << idx << " est invalide." << std::endl;
	if (slots[idx])
	{
		std::cout << "UNEQUIP " << slots[idx]->getType() << " at slot " << idx << "." << std::endl;
		slots[idx] = 0;
	}
	else
		std::cerr << "ERROR Unequip: No AMateria at slot " << idx << "." << std::endl;
}

void	Character::use(int idx, ICharacter& target)
{
	if (idx < 0 || idx >= SLOTS)
		std::cerr << "ERROR Use: Indice slot " << idx << " est invalide." << std::endl;
	if (slots[idx])
		slots[idx]->use(target);
	else
		std::cerr << "ERROR Use: No AMateria at slot " << idx << "." << std::endl;
}
