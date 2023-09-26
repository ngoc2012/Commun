/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phonebook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 18:45:45 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/26 21:43:20 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phonebook.h"

Contact::Contact(){}
Contact::~Contact(){}

PhoneBook::PhoneBook(){}
PhoneBook::~PhoneBook(){}

int	main(void)
{
	PhoneBook	b;

	std::string	input = "";
	std::cout << "Phone Book\n";
	while (input.compare("EXIT")) {
		if (input.compare("ADD") == 0)
			b.add();
		else if (input.compare("SEARCH") == 0) {
			b.printContacts();
			b.search();
		}
		std::cout << "> " << std::flush;
		std::cin >> input;
	}
	return (0);
}
