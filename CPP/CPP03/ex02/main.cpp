/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:17:48 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/06 17:23:07 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"

int main()
{
	std::cout << "Test constructor and destructor" << std::endl;
	ScavTrap clap4;
	std::cout << "====================================" << std::endl;
	std::cout << "Test methods" << std::endl;
	clap4.setName("Clap4");
	ScavTrap clap5(clap4);
	clap5.setName("Clap5");
	clap5.guardGate();
	std::cout << "====================================" << std::endl;
	ClapTrap clap1("Clap1");
	ScavTrap clap6 = clap5;
	clap6.setName("Clap6");
	clap6.guardGate();
	std::cout << "====================================" << std::endl;
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
	std::cout << clap1;
	std::cout << clap2;
	clap3.attack(clap1.getName());
	clap1.takeDamage(clap3.getAttackDamage());
	std::cout << clap1;
	std::cout << clap3;
	for (int i = 0; i < 10; i++)
	{
		clap1.attack(clap2.getName());
		clap2.takeDamage(clap1.getAttackDamage());
		std::cout << clap1;
		std::cout << clap2;
	}
	clap3.attack(clap4.getName());
	clap4.takeDamage(clap3.getAttackDamage());
	std::cout << clap3;
	std::cout << clap4;
	clap4.beRepaired(1);
	std::cout << clap4;
	clap4.attack(clap3.getName());
	clap3.takeDamage(clap4.getAttackDamage());
	std::cout << clap3;
	std::cout << clap4;
	clap2.beRepaired(5);
	clap1.beRepaired(2);
	clap3.beRepaired(1);
	std::cout << clap1;
	std::cout << clap2;
	std::cout << clap3;
	std::cout << clap6;
	return (0);
}
