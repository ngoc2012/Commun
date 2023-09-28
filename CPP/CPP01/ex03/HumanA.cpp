/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 07:28:24 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/28 08:53:27 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanA.hpp"

HumanA::HumanA(std::string s, Weapon& w) : name(s), weapon(w) {}
HumanA::~HumanA(void) {}

void	HumanA::attack(void) const
{
	std::cout << name << " attacks with their " <<  weapon.getType() << std::endl;
}
