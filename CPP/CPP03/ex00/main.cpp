/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:17:48 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/30 19:17:52 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

int main()
{
	std::cout << std::endl;
    FragTrap clap("Pierrot");
    FragTrap trap("Michel");
    
	std::cout << std::endl;
    clap.rangedAttack("Michel");
    trap.takeDamage(20);
    clap.meleeAttack("Michel");
    trap.takeDamage(30);
    trap.beRepaired(35);
    trap.beRepaired(80);
    trap.takeDamage(120);
    trap.beRepaired(33);
    
    clap.vaulthunter_dot_exe("Michel");
    clap.vaulthunter_dot_exe("Michel");
    clap.vaulthunter_dot_exe("Michel");
    clap.vaulthunter_dot_exe("Michel");
    clap.vaulthunter_dot_exe("Michel");
    
	std::cout << std::endl;
    return (0);
}
