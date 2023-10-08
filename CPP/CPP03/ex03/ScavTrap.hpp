/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:50:42 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/08 07:11:22 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCAVTRAP_HPP
# define SCAVTRAP_HPP

#include "ClapTrap.hpp"

class ScavTrap : virtual public ClapTrap
{
	protected:
		unsigned int	_energy_points;
	public:
		ScavTrap();
		ScavTrap(std::string name);
		ScavTrap(const ScavTrap& src);
		ScavTrap	&operator=( const ScavTrap &src );
		~ScavTrap();

		void	welcome(void) const;
		void	attack(const std::string& target);
		void	guardGate() const;
};

#endif
