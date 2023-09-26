/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phonebook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 18:45:45 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/26 21:57:22 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phonebook.h"

Contact::Contact(){}

Contact::~Contact(){}

Contact::show()
{
	std::cout << "|" << std::setw(10) << index << std::flush;
	std::cout << "|" << std::setw(10) << this->_printLen(this->_firstName) << std::flush;
	std::cout << "|" << std::setw(10) << this->_printLen(this->_lastName) << std::flush;
	std::cout << "|" << std::setw(10) << this->_printLen(this->_nickname) << std::flush;
	std::cout << "|" << std::endl;
}

PhoneBook::PhoneBook(){}

PhoneBook::~PhoneBook(){}

PhoneBook::add()
{
	static int	i;
	Contact	*new = this->contacts[i % 8];

	std::cout << "add\n";
	//std::cout << "> " << std::flush;
	//std::cin >> input;
	i++
}

PhoneBook::search()
{
	std::cout << "search\n";
	//std::cout << "> " << std::flush;
	//std::cin >> input;
}

PhoneBook::show()
{
	std::cout << "show\n";
	//std::cout << "> " << std::flush;
	//std::cin >> input;
}

int	main(void)
{
	PhoneBook	b;

	std::string	input = "";
	std::cout << "Phone Book\n";
	while (input.compare("EXIT")) {
		if (input.compare("ADD") == 0)
			b.add();
		else if (input.compare("SEARCH") == 0) {
			b.show();
			b.search();
		}
		std::cout << "> " << std::flush;
		std::cin >> input;
	}
	return (0);
}
