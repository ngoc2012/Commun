/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/08 06:55:47 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap() : ClapTrap()
{
	name = std::string("RandomFrag");
	hit_points = FragTrap::hit_points;
	energy_points = ScavTrap::energy_points;
	attack_damage = FragTrap::attack_damage;
	max_hit = FragTrap::max_hit;
	welcome(); 
}

DiamondTrap::DiamondTrap(std::string name) : ClapTrap(name)
{
	hit_points = FragTrap::hit_points;
	energy_points = ScavTrap::energy_points;
	attack_damage = FragTrap::attack_damage;
	max_hit = FragTrap::max_hit;
	welcome(); 
}

DiamondTrap::DiamondTrap(const DiamondTrap& src) : ClapTrap(src), ScavTrap(src), FragTrap(src)
{
	std::cout << "Another ";
	welcome();
}

DiamondTrap&	DiamondTrap::operator=( DiamondTrap const & src )
{
	name = src.name;
	hit_points = src.hit_points;
	energy_points = src.energy_points;
	attack_damage = src.attack_damage;
	max_hit = src.max_hit;
	std::cout << "Another ";
	return (*this);
}

DiamondTrap::~DiamondTrap() { std::cout << "DiamondTrap " << name << " quit game." << std::endl; }

void	DiamondTrap::whoAmI(void) const
{
	std::cout << "DiamondTrap " << name << " has ClapTrap name " << ClapTrap::name << "." << std::endl;
}

void	DiamondTrap::welcome(void) const
{
	std::cout << "DiamondTrap " << getName()
	<< " (hit points: " << getHitPoints()
	<< ", energy points: " << getEnergyPoints()
	<< ", attack_damage: " << getAttackDamage()
	<< ", max hit: " << getMaxHit()
	<< ") join the game." << std::endl;
}

void	DiamondTrap::attack(std::string const & target)
{
	ScavTrap::attack(target);
}
