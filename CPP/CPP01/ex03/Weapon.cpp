/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 07:33:36 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/28 08:48:14 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

Weapon::~Weapon(void) {}
Weapon::Weapon(std::string s) : type(s) {}

const std::string&	Weapon::getType(void) const
{
	return (type);
}

void	Weapon::setType(std::string s)
{
	type = s;
}
