/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/05 09:57:15 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

void	ScavTrap::welcome(void) override {
	std::cout << "ScavTrap " << getName()
	<< " (hit points: " << getHitPoints()
	<< ", energy points: " << getEnergyPoints()
	<< ", attack_damage: " << getAttackDamage()
	<< ", max hit: " << getMaxHit()
	<< ") join the game." << std::endl;
}

ScavTrap::ScavTrap() : ClapTrap()
{
	name = std::string("RandomScav");
	hit_points = 100;
	energy_points = 50;
	attack_damage = 20;
	welcome(); 
}

ScavTrap::ScavTrap(std::string name) : ClapTrap(name)
{
	hit_points = 100;
	energy_points = 50;
	attack_damage = 20;
	welcome(); 
}


void	ScavTrap::guardGate()
{
	std::cout << "ScavTrap " << name << " guard gate." << std::endl;
}
//ScavTrap::ScavTrap(const ScavTrap& src)
//:
//	name(src.name),
//	hit_points(src.hit_points),
//	energy_points(src.energy_points),
//	attack_damage(src.attack_damage)
//{ welcome(*this); }
//
//ScavTrap::~ScavTrap() { std::cout << "ScavTrap " << name << " quit game." << std::endl; }

//void	ScavTrap::attack(std::string const & target)
//{
//	if (energy_points && hit_points)
//	{
//		std::cout << "ScavTrap " << name << " attack " << target << ", causing " << attack_damage << " points of damage!" << std::endl;
//		energy_points--;
//	}
//	else
//		std::cout << "Alert!!! ScavTrap " << name << " tried to attack but has no more energy or hit." << std::endl;
//}
//
//void	ScavTrap::takeDamage(unsigned int amount)
//{
//	std::cout << "ScavTrap " << name << " takes " << amount <<" damages." << std::endl;
//	if (amount > hit_points)
//		amount = hit_points;
//	hit_points -= amount;
//}
//
//void	ScavTrap::beRepaired(unsigned int amount)
//{
//	if (energy_points && hit_points)
//	{
//		hit_points += amount;
//		if (hit_points > max_hit)
//			hit_points = max_hit;
//		std::cout << "ScavTrap " << name << " is repaired " << amount << " points (" << hit_points << "  hit points)." << std::endl;
//		energy_points--;
//	}
//	else
//		std::cout << "Alert!!! ScavTrap " << name << " tried to be repaired but has no more energy or hit." << std::endl;
//}
//
//std::string	ScavTrap::getName(void) const { return (name); }
//unsigned int	ScavTrap::getHitPoints(void) const { return (hit_points); }
//unsigned int	ScavTrap::getEnergyPoints(void) const { return (energy_points); }
//unsigned int	ScavTrap::getAttackDamage(void) const { return (attack_damage); }
//
//void		ScavTrap::setName(std::string s)
//{
//	std::cout << "ScavTrap " << name << " now named " << s << "." << std::endl;
//	name = s;
//}
//void		ScavTrap::setHitPoints(unsigned int n) { hit_points = n; }
//void		ScavTrap::setEnergyPoints(unsigned int n) { energy_points = n; }
//void		ScavTrap::setAttackDamage(unsigned int n)
//{
//	std::cout << "ScavTrap " << name << " now has " << n << " attack damage." << std::endl;
//	attack_damage = n;
//}
//
//void		ScavTrap::status(void)
//{
//	std::cout << "ScavTrap " << name << " now has "
//	<< hit_points << " hit points, "
//	<< energy_points << " energy point." << std::endl;
//}
