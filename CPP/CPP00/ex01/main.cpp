/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 18:45:45 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/27 09:46:39 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

int	main(void)
{
	std::string	input;
	PhoneBook	b;

	std::cout << "Phone Book\n> ";
	while (std::cin >> input) {
		if (!input.compare("ADD"))
			b.add();
		else if (!input.compare("SEARCH"))
			b.search();
		else if (!input.compare("EXIT"))
			return (0);
		std::cout << "> " << std::flush;
	}
	return (0);
}
