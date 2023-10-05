/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/05 10:42:41 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

ScavTrap::ScavTrap() : ClapTrap()
{
	name = std::string("RandomScav");
	hit_points = 100;
	energy_points = 50;
	attack_damage = 20;
	max_hit = 100;
	welcome(); 
}

ScavTrap::ScavTrap(std::string name) : ClapTrap(name)
{
	hit_points = 100;
	energy_points = 50;
	attack_damage = 20;
	max_hit = 100;
	welcome(); 
}

ScavTrap::ScavTrap(const ScavTrap& src)
:
	ClapTrap(src)
{
	std::cout << "A copy of ";
	welcome();
}

ScavTrap::~ScavTrap() { std::cout << "ScavTrap " << name << " quit game." << std::endl; }

void	ScavTrap::guardGate()
{
	std::cout << "ScavTrap " << name << " is now in gate keeper mode." << std::endl;
}

void	ScavTrap::welcome(void) {
	std::cout << "ScavTrap " << getName()
	<< " (hit points: " << getHitPoints()
	<< ", energy points: " << getEnergyPoints()
	<< ", attack_damage: " << getAttackDamage()
	<< ", max hit: " << getMaxHit()
	<< ") join the game." << std::endl;
}

void	ScavTrap::attack(std::string const & target)
{
	if (energy_points && hit_points)
	{
		std::cout << "ScavTrap " << name << " attack " << target << ", causing " << attack_damage << " points of damage!" << std::endl;
		energy_points--;
	}
	else
		std::cout << "Alert!!! ScavTrap " << name << " tried to attack but has no more energy or hit." << std::endl;
}
