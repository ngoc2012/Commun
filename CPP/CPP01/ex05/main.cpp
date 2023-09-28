/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 18:45:45 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/28 11:56:47 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Harl.hpp"

int	main(void)
{
	Harl	h;

	std::string	input = "";
	std::cout << "Harl program\n";
	std::cout << "Command: DEBUG INFO WARNING ERROR EXIT\n";
	while (input.compare("EXIT")) {
		std::cout << "> " << std::flush;
		std::cin >> input;
		h.complain(input);
	}
	return (0);
}
