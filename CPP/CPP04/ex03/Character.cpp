/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/12 11:30:23 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Character.hpp"

Character::Character()
{
	type = "ice";
	std::cout << type << " default constructor." << std::endl;
}
Character::Character(const Character& src) {
	type = src.type;
	*this = src;
	std::cout << type << " copy constructor." << std::endl;
}
Character&	Character::operator=( Character const & src )
{
	type = src.type;
	return (*this);
}
Character::~Character() { std::cout type << " destructor." << std::endl; }
void	Character::use(ICharacter& target)
{
	std::cout << "* shoots an ice bolt at " << target.type << " *" << std:endl;
}
