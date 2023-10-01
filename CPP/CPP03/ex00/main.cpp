/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:17:48 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/01 20:37:33 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

int main()
{
	std::cout << std::endl;
	ClapTrap clap1("Clap1");
	ClapTrap clap2;
	ClapTrap clap3(clap1);

	clap2.setName("Clap2");
	clap3.setName("Clap3");
	clap1.setAttackDamage(1);
	clap2.setAttackDamage(2);
	clap3.setAttackDamage(3);
	clap1.attack(clap2.getName());
	clap2.takeDamage(clap1.getAttackDamage());
	clap3.attack(clap1.getName());
	clap1.takeDamage(clap3.getAttackDamage());
	return (0);
}
