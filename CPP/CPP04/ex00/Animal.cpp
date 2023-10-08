/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/08 14:55:37 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

Animal::Animal() {std::cout << "Animal constructor" << std::endl;}
Animal::Animal(const Animal& src) {
	*this = src;
	std::cout << "Animal copy constructor" << std::endl
}

Animal&	Animal::operator=( Animal const & src )
{
	name = src.name;
	hit_points = src.hit_points;
	energy_points = src.energy_points;
	attack_damage = src.attack_damage;
	std::cout << "Another ";
	return (*this);
}

Animal::~Animal() { std::cout << "Animal " << name << " quit game." << std::endl; }

std::ostream    &operator<<( std::ostream &o, const Animal &c )
{
	o << "Animal " << c.getName() << " now has "
	<< c.getHitPoints() << " hit points, "
	<< c.getEnergyPoints() << " energy point." << std::endl;
	return o;
}

void	Animal::attack(std::string const & target)
{
	if (energy_points && hit_points)
	{
		std::cout << "Animal " << name << " attack " << target << ", causing " << attack_damage << " points of damage!" << std::endl;
		energy_points--;
	}
	else
		std::cout << "Alert!!! Animal " << name << " tried to attack but has no more energy or hit." << std::endl;
}

void	Animal::takeDamage(unsigned int amount)
{
	std::cout << "Animal " << name << " takes " << amount <<" damages." << std::endl;
	if (amount > hit_points)
		amount = hit_points;
	hit_points -= amount;
}

void	Animal::beRepaired(unsigned int amount)
{
	if (energy_points && hit_points)
	{
		hit_points += amount;
		if (hit_points > max_hit)
			hit_points = max_hit;
		std::cout << "Animal " << name << " is repaired " << amount << " points (" << hit_points << "  hit points)." << std::endl;
		energy_points--;
	}
	else
		std::cout << "Alert!!! Animal " << name << " tried to be repaired but has no more energy or hit." << std::endl;
}

std::string	Animal::getName(void) const { return (name); }
unsigned int	Animal::getHitPoints(void) const { return (hit_points); }
unsigned int	Animal::getEnergyPoints(void) const { return (energy_points); }
unsigned int	Animal::getAttackDamage(void) const { return (attack_damage); }

void		Animal::setName(std::string s)
{
	std::cout << "Animal " << name << " now named " << s << "." << std::endl;
	name = s;
}
void		Animal::setAttackDamage(unsigned int n)
{
	std::cout << "Animal " << name << " now has " << n << " attack damage." << std::endl;
	attack_damage = n;
}
