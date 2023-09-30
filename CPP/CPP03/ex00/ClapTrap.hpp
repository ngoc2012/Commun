/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:50:42 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/30 19:57:36 by ngoc             ###   ########.fr       */
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
		//unsigned int	max_hit_points;
		//unsigned int	max_energy_points;
		//unsigned int	level;
		//unsigned int	melee_attack_damage;
		//unsigned int	ranged_attack_damage;
		//unsigned int	armor_damage_reduction;
		//void		mathAttack(std::string const & target);
		//void		questionAttack(std::string const & target);
		//void		danseAttack(std::string const & target);
		//void		lostAttack(std::string const & target);
		//void		monologueAttack(std::string const & target);

	public:
		ClapTrap();
		ClapTrap(std::string name);
		ClapTrap(const ClapTrap&);
		virtual ~ClapTrap();
		ClapTrap &operator=(const ClapTrap& op);
		//void		rangedAttack(std::string const & target);
		//void		meleeAttack(std::string const & target);
		//void		vaulthunter_dot_exe(const std::string& target);
		void		attack(const std::string& target);
		void		takeDamage(unsigned int amount);
		void		beRepaired(unsigned int amount);
};

#endif
