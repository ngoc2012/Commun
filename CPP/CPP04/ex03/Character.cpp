/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/12 13:36:14 by minh-ngu         ###   ########.fr       */
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
void	Character::use(ICharacter& target)
{
	std::cout << "* shoots an ice bolt at " << target.type << " *" << std:endl;
}
