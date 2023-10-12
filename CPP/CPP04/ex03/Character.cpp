/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/12 13:52:27 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Character.hpp"

Character::Character()
{
	for (int i = 0; i < SLOTS; i++) {slots[i] = 0;}
	std::cout << "Character default constructor." << std::endl;
}
Character::Character(const Character& src) {
	*this = src;
	std::cout << "Character copy constructor." << std::endl;
}
Character&	Character::operator=( Character const & src )
{
	for (int i = 0; i < SLOTS; i++) {slots[i] = src.slots[i];}
	return (*this);
}
Character::~Character() { std::cout << "Character destructor." << std::endl; }
void	Character::equip(AMateria* m)
{
	int	i = 0;
	while (i < SLOTS && slots[i])
		i++;
	if (i == SLOTS - 1)
	{
		std::cerr << "Character slots are full." << std::endl;
		return ;
	}
	slots[i] = m;
}
void	Character::unequip(int idx)
{
	if (idx < 0 || idx >= SLOTS)
		std::cerr << "Indice slot " << idx << " est invalide." << std::endl;
	if (slots[idx])
		slots[idx] = 0;
	else
		std::cerr << "No AMateria at slot " << idx << "." << std::endl;
}
void	Character::use(int idx, ICharacter& target)
{
	if (idx < 0 || idx >= SLOTS)
		std::cerr << "Indice slot " << idx << " est invalide." << std::endl;
	if (slots[idx])
		slots[idx]->use(target);
	else
		std::cerr << "No AMateria at slot " << idx << "." << std::endl;
}
