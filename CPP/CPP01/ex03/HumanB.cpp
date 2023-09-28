/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 07:28:24 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/28 09:37:03 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanB.hpp"

HumanB::HumanB(std::string s) : name(s) {}
HumanB::~HumanB(void) {}

void	HumanB::attack(void) const
{
	std::cout << name << " attacks with their " <<  weapon->getType() << std::endl;
}

void	HumanB::setWeapon(Weapon& w)
{
	weapon = &w;
}
