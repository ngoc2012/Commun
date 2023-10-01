/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/01 17:09:40 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

void	welcome(ClapTrap &c) {
	std::cout << "ClapTrap " << name
	<< "(hit points: " << hit_points
	<< ", energy points: " << energy_points
	<< ", attack_damage: " << attack_damage
	<< ") join the game\n";
}

ClapTrap::ClapTrap()
{
	name = std::string("RANDOM");
	welcome(&this); 
}

ClapTrap::ClapTrap(std::string name)
:
	name(name),
	hit_points(10),
	energy_points(10),
	attack_damage(0)
{ welcome(&this); }

ClapTrap::ClapTrap(const ClapTrap& src)
:
	name(src.name),
	hit_points(src.hit_points),
	energy_points(src.energy_points),
	attack_damage(src.attack_damage)
{ welcome(&this); }

ClapTrap::~ClapTrap() { std::cout << "ClapTrap " << name << " quit game." << std::endl; }

void	ClapTrap::attack(std::string const & target)
{
	if (energy_points)
	{
		std::cout << "ClapTrap " << name << " attack " << target.name << ", causing " << attack_damage << " points of damage!" << std::endl;
		target.hit_points -= attack_damage;
		energy_points--;
	}
	else
		std::cout << "ClapTrap " << name << " has no more energy." << std::endl;
}

void	ClapTrap::takeDamage(unsigned int amount)
{
	std::cout << "ClapTrap " << name << " takes " << amount <<" damages." << std::endl;
	hit_points -= amount;
}

void	ClapTrap::beRepaired(unsigned int amount)
{
	if (energy_points)
	{
		hit_points += amount;
		std::cout << "ClapTrap " << name << " is repaired " << amout << " points (" << hit_points << "  hit points)." << std::endl;
		energy_points--;
	}
	else
		std::cout << "ClapTrap " << name << " has no more energy." << std::endl;
}
