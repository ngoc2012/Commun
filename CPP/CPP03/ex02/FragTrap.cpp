/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/07 16:30:56 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

FragTrap::FragTrap() : ClapTrap()
{
	name = std::string("RandomFrag");
	hit_points = 100;
	energy_points = 100;
	attack_damage = 30;
	max_hit = 100;
	welcome(); 
}

FragTrap::FragTrap(std::string s) : ClapTrap(s)
{
	hit_points = 100;
	energy_points = 100;
	attack_damage = 30;
	max_hit = 100;
	welcome(); 
}

FragTrap::FragTrap(const FragTrap& src)
:
	ClapTrap(src)
{
	std::cout << "Another ";
	welcome();
}

FragTrap&	FragTrap::operator=( FragTrap const & src )
{
	ClapTrap::operator=(src);
	return (*this);
}

FragTrap::~FragTrap() { std::cout << "FragTrap " << name << " quit game." << std::endl; }

void	FragTrap::highFivesGuys(void) const
{
	std::cout << "FragTrap " << name << " request high fives." << std::endl;
}

void	FragTrap::welcome(void) const
{
	std::cout << "FragTrap " << getName()
	<< " (hit points: " << getHitPoints()
	<< ", energy points: " << getEnergyPoints()
	<< ", attack_damage: " << getAttackDamage()
	<< ", max hit: " << getMaxHit()
	<< ") join the game." << std::endl;
}

void	FragTrap::attack(std::string const & target)
{
	if (energy_points && hit_points)
	{
		std::cout << "FragTrap " << name << " attack " << target << ", causing " << attack_damage << " points of damage!" << std::endl;
		energy_points--;
	}
	else
		std::cout << "Alert!!! FragTrap " << name << " tried to attack but has no more energy or hit." << std::endl;
}
