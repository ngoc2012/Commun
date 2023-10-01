/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:50:42 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/01 18:43:08 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLAPTRAP_HPP
# define CLAPTRAP_HPP

#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>

class ClapTrap;

class ClapTrap
{
	private:
		std::string	name;
		unsigned int	hit_points;
		unsigned int	energy_points;
		unsigned int	attack_damage;

	public:
		ClapTrap();
		ClapTrap(std::string name);
		ClapTrap(const ClapTrap&);
		ClapTrap &operator=(const ClapTrap& op);
		void		attack(const std::string& target);
		void		takeDamage(unsigned int amount);
		void		beRepaired(unsigned int amount);

		std::string	getName(void) const;
		unsigned int	getHitPoints(void) const;
		unsigned int	getEnergyPoints(void) const;

		void		setName(std::string) const;
		void		setHitPoints(unsigned int) const;
		void		setEnergyPoints(unsigned int) const;
		//virtual ~ClapTrap();
};

#endif
