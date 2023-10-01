/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/01 19:15:49 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

void	welcome(ClapTrap &c) {
	std::cout << "ClapTrap " << c.getName()
	<< "(hit points: " << c.getHitPoints()
	<< ", energy points: " << c.getEnergyPoints()
	<< ", attack_damage: " << c.getAttackDamage()
	<< ") join the game." << std::endl;
}

ClapTrap::ClapTrap()
{
	name = std::string("RANDOM");
	welcome(*this); 
}

ClapTrap::ClapTrap(std::string name)
:
	name(name),
	hit_points(10),
	energy_points(10),
	attack_damage(0)
{ std::cout << "Another "; welcome(*this); }

ClapTrap::ClapTrap(const ClapTrap& src)
:
	name(src.name),
	hit_points(src.hit_points),
	energy_points(src.energy_points),
	attack_damage(src.attack_damage)
{ welcome(*this); }

ClapTrap::~ClapTrap() { std::cout << "ClapTrap " << name << " quit game." << std::endl; }

void	ClapTrap::attack(std::string const & target)
{
	if (energy_points)
	{
		std::cout << "ClapTrap " << name << " attack " << target.getName() << ", causing " << attack_damage << " points of damage!" << std::endl;
		target.setHitPoints(target.getHitPoints() - attack_damage);
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

std::string	getName(void) const { return (name); }
unsigned int	getHitPoints(void) const { return (hit_points); }
unsigned int	getEnergyPoints(void) const { return (energy_points); }
unsigned int	getAttackDamage(void) const { return (attack_damage); }

void		setName(std::string s) { name = s; }
void		setHitPoints(unsigned int n) { hit_points = n; }
void		setEnergyPoints(unsigned int n) { energy_points = n; }
void		setAttackDamage(unsigned int n) { attack_damage = n; }
