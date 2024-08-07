/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/08 07:28:16 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

void	ClapTrap::welcome(void) {
	std::cout << "ClapTrap " << name
	<< " (hit points: " << hit_points
	<< ", energy points: " << energy_points
	<< ", attack damage: " << attack_damage
	<< ", max hit: " << max_hit
	<< ") join the game." << std::endl;
}

ClapTrap::ClapTrap()
{
	name = std::string("RandomClap");
	hit_points = 10;
	energy_points = 10;
	attack_damage = 0;
	welcome(); 
}

ClapTrap::ClapTrap(std::string s)
:
	name(s),
	hit_points(10),
	energy_points(10),
	attack_damage(0)
{ welcome(); }

/*
When you define a copy constructor or a copy assignment operator for a class, those functions are considered as part of the class itself, and they have special access rights to access the private members of the class. This is known as "special member function access" or "access control within the class."
*/

ClapTrap::ClapTrap(const ClapTrap& src)
:
	name(src.name),
	hit_points(src.hit_points),
	energy_points(src.energy_points),
	attack_damage(src.attack_damage)
{ std::cout << "Another "; welcome(); }

ClapTrap&	ClapTrap::operator=( ClapTrap const & src )
{
	name = src.name;
	hit_points = src.hit_points;
	energy_points = src.energy_points;
	attack_damage = src.attack_damage;
	std::cout << "Another ";
	return (*this);
}

ClapTrap::~ClapTrap() { std::cout << "ClapTrap " << name << " quit game." << std::endl; }

std::ostream    &operator<<( std::ostream &o, const ClapTrap &c )
{
	o << "ClapTrap " << c.getName() << " now has "
	<< c.getHitPoints() << " hit points, "
	<< c.getEnergyPoints() << " energy point." << std::endl;
	return o;
}

void	ClapTrap::attack(std::string const & target)
{
	if (energy_points && hit_points)
	{
		std::cout << "ClapTrap " << name << " attack " << target << ", causing " << attack_damage << " points of damage!" << std::endl;
		energy_points--;
	}
	else
		std::cout << "Alert!!! ClapTrap " << name << " tried to attack but has no more energy or hit." << std::endl;
}

void	ClapTrap::takeDamage(unsigned int amount)
{
	std::cout << "ClapTrap " << name << " takes " << amount <<" damages." << std::endl;
	if (amount > hit_points)
		amount = hit_points;
	hit_points -= amount;
}

void	ClapTrap::beRepaired(unsigned int amount)
{
	if (energy_points && hit_points)
	{
		hit_points += amount;
		if (hit_points > max_hit)
			hit_points = max_hit;
		std::cout << "ClapTrap " << name << " is repaired " << amount << " points (" << hit_points << "  hit points)." << std::endl;
		energy_points--;
	}
	else
		std::cout << "Alert!!! ClapTrap " << name << " tried to be repaired but has no more energy or hit." << std::endl;
}

std::string	ClapTrap::getName(void) const { return (name); }
unsigned int	ClapTrap::getHitPoints(void) const { return (hit_points); }
unsigned int	ClapTrap::getEnergyPoints(void) const { return (energy_points); }
unsigned int	ClapTrap::getAttackDamage(void) const { return (attack_damage); }

void		ClapTrap::setName(std::string s)
{
	std::cout << "ClapTrap " << name << " now named " << s << "." << std::endl;
	name = s;
}
void		ClapTrap::setAttackDamage(unsigned int n)
{
	std::cout << "ClapTrap " << name << " now has " << n << " attack damage." << std::endl;
	attack_damage = n;
}
