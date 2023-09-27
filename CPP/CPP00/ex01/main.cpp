/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 18:45:45 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/27 09:41:49 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

int	main(void)
{
	PhoneBook	b;

	std::string	input = "";
	std::cout << "Phone Book\n";
	while (std::cin >> input) {
		if (input.compare("ADD") == 0)
			b.add();
		else if (input.compare("SEARCH") == 0)
			b.search();
		else if (input.compare("SEARCH") == 0)
			break;
		std::cout << "> " << std::flush;
	}
	if (std::cin.eof()) {
		std::cout << "End of input reached (Ctrl+D was pressed)." << std::endl;
	} else {
		std::cout << "Input error occurred." << std::endl;
	}
	return (0);
}
