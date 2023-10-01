/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:17:48 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/01 17:20:11 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

int main()
{
	std::cout << std::endl;
	ClapTrap clap1("Clap1");
	ClapTrap clap2;
	ClapTrap clap3(clap1);

	std::cout << std::endl;
	clap.rangedAttack("Michel");
	trap.takeDamage(20);
	clap.meleeAttack("Michel");
	trap.takeDamage(30);
	trap.beRepaired(35);
	trap.beRepaired(80);
	trap.takeDamage(120);
	trap.beRepaired(33);

	std::cout << std::endl;
	return (0);
}
