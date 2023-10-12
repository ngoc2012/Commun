/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/12 13:41:12 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Character.hpp"

Character::Character()
{
	for (int i; i < SLOTS; i++) {slots[i] = 0;}
	std::cout << "Character default constructor." << std::endl;
}
Character::Character(const Character& src) {
	*this = src;
	std::cout << "Character copy constructor." << std::endl;
}
Character&	Character::operator=( Character const & src )
{
	for (int i; i < SLOTS; i++) {slots[i] = src.slots[i];}
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
}
void	unequip(int idx)
{
}
void	Character::use(ICharacter& target)
{
	std::cout << "* shoots an ice bolt at " << target.type << " *" << std:endl;
}
