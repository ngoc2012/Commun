/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/06 13:28:13 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

void	welcome(ClapTrap &c) {
	std::cout << "ClapTrap " << c.getName()
	<< " (hit points: " << c.getHitPoints()
	<< ", energy points: " << c.getEnergyPoints()
	<< ", attack_damage: " << c.getAttackDamage()
	<< ") join the game." << std::endl;
}

ClapTrap::ClapTrap()
{
	name = std::string("RandomClap");
	hit_points = 10;
	energy_points = 10;
	attack_damage = 0;
	welcome(*this); 
}

ClapTrap::ClapTrap(std::string name)
:
	name(name),
	hit_points(10),
	energy_points(10),
	attack_damage(0)
{ welcome(*this); }

ClapTrap::ClapTrap(const ClapTrap& src)
:
	name(src.name),
	hit_points(src.hit_points),
	energy_points(src.energy_points),
	attack_damage(src.attack_damage)
{ std::cout << "Another "; welcome(*this); }

ClapTrap::~ClapTrap() { std::cout << "ClapTrap " << name << " quit game." << std::endl; }

ClapTrap&	ClapTrap::operator=( ClapTrap const & src )
{
	name = src.name;
	hit_points = src.getHitPoints();
	energy_points = src.getEnergyPoints();
	attack_damage = src.getAttackDamage();
	return (*this);
}

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
