/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 18:45:45 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/28 12:39:28 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Harl.hpp"

int	main(int argc, char **argv)
{
	Harl	h;

	if (argc != 2)
		return (1);
	std::string	input = "";
	std::cout << "Harl program\n";
	std::cout << "Command: DEBUG INFO WARNING ERROR EXIT\n> ";
	while (std::getline(std::cin, input))
	{
		if (!input.compare("EXIT"))
			return (0);
		h.complain(input);
		std::cout << "> " << std::flush;
	}
	std::cout << "[ Probably complaining about insignificant problems ]\n";
	return (0);
}
