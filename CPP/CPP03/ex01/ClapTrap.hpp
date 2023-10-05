/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:50:42 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/05 09:57:43 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLAPTRAP_HPP
# define CLAPTRAP_HPP

#include <iostream>

class ClapTrap
{
	protected:
		std::string	name;
		unsigned int	hit_points;
		unsigned int	energy_points;
		unsigned int	attack_damage;
		static const unsigned int	max_hit = 10;
	public:
		ClapTrap();
		ClapTrap(std::string name);
		ClapTrap(const ClapTrap&);
		ClapTrap &operator=(const ClapTrap& op);
		~ClapTrap();

		void		attack(const std::string& target);
		void		takeDamage(unsigned int amount);
		void		beRepaired(unsigned int amount);
		virtual void		welcome(void);

		std::string	getName(void) const;
		unsigned int	getHitPoints(void) const;
		unsigned int	getEnergyPoints(void) const;
		unsigned int	getAttackDamage(void) const;
		unsigned int	getMaxHit(void) const;

		void		setName(std::string);
		void		setHitPoints(unsigned int);
		void		setEnergyPoints(unsigned int);
		void		setAttackDamage(unsigned int);

		void		status(void);
};

#endif
