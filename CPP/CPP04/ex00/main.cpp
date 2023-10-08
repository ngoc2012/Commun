/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:17:48 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/06 13:26:37 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

int main()
{
	std::cout << std::endl;
	std::cout << "clap1 constructor" << std::endl;
	ClapTrap clap1("Clap1");
	std::cout << "clap2 constructor" << std::endl;
	ClapTrap clap2;
	std::cout << "clap3 constructor" << std::endl;
	ClapTrap clap3(clap1);
	std::cout << "clap4 constructor" << std::endl;
	ClapTrap clap4 = clap1;

	clap2.setName("Clap2");
	clap3.setName("Clap3");
	clap4.setName("Clap4");
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
	clap2.beRepaired(5);
	clap1.beRepaired(2);
	clap3.beRepaired(1);
	std::cout << clap1;
	std::cout << clap2;
	std::cout << clap3;
	return (0);
}
