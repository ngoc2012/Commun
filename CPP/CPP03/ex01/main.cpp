/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:17:48 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/05 10:19:15 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

int main()
{
	std::cout << "Test constructor and destructor" << std::endl;
	ScavTrap clap4;
	std::cout << "====================================" << std::endl;
	std::cout << "Test methods" << std::endl;
	clap4.setName("Clap4");
	std::cout << std::endl;
	ClapTrap clap1("Clap1");
	ClapTrap clap2;
	ClapTrap clap3(clap1);

	clap2.setName("Clap2");
	clap3.setName("Clap3");
	clap4.setName("Clap4");
	clap4.guardGate();
	clap1.setAttackDamage(1);
	clap2.setAttackDamage(2);
	clap3.setAttackDamage(3);
	clap1.attack(clap2.getName());
	clap2.takeDamage(clap1.getAttackDamage());
	clap1.status();
	clap2.status();
	clap3.attack(clap1.getName());
	clap1.takeDamage(clap3.getAttackDamage());
	clap1.status();
	clap3.status();
	for (int i = 0; i < 10; i++)
	{
		clap1.attack(clap2.getName());
		clap2.takeDamage(clap1.getAttackDamage());
		clap1.status();
		clap2.status();
	}
	clap4.attack(clap3.getName());
	clap3.takeDamage(clap4.getAttackDamage());
	clap3.status();
	clap4.status();
	clap2.beRepaired(5);
	clap1.beRepaired(2);
	clap3.beRepaired(1);
	clap1.status();
	clap2.status();
	clap3.status();
	return (0);
}
