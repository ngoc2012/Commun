/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/05 10:13:18 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

void	ScavTrap::welcome(void) {
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


void	ScavTrap::guardGate()
{
	std::cout << "ScavTrap " << name << " guard gate." << std::endl;
}

ScavTrap::~ScavTrap() { std::cout << "ScavTrap " << name << " quit game." << std::endl; }
