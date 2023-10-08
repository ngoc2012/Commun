/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:17:48 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/08 07:15:34 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"

int main()
{
	std::cout << "Test constructor and destructor" << std::endl;
	DiamondTrap clap10;
	clap10.setName("Diamond10");
	std::cout << clap10;
	DiamondTrap clap11 = clap10;
	std::cout << clap11;
	clap10.attack("sdfd");
	/*
	std::cout << "Constructor clap 7" << std::endl;
	FragTrap clap7;
	std::cout << "Constructor clap 8" << std::endl;
	FragTrap clap8(clap7);
	std::cout << "Constructor clap 9" << std::endl;
	FragTrap clap9 = clap8;
	std::cout << "====================================" << std::endl;
	std::cout << "Test methods" << std::endl;
	clap7.setName("Clap7");
	clap8.setName("Clap8");
	clap9.setName("Clap9");
	clap7.highFivesGuys();
	clap8.highFivesGuys();
	clap9.highFivesGuys();
	ScavTrap clap4;
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
	*/
}
