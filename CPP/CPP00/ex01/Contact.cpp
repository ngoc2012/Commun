/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 18:45:45 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/27 06:25:54 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

std::string printLen(std::string str, int len) {
	if (str.length() > len)
		return str.substr(0, len - 1) + ".";
	return str;
}

Contact::Contact(){}

Contact::~Contact(){}

void Contact::show(int index) const
{
	std::cout << "|" << std::setw(WIDTH) << index << std::flush;
	std::cout << "|" << std::setw(WIDTH) << printLen(this->_firstName, WIDTH) << std::flush;
	std::cout << "|" << std::setw(WIDTH) << printLen( this->_lastName, WIDTH) << std::flush;
	std::cout << "|" << std::setw(WIDTH) << printLen( this->_nickname, WIDTH) << std::flush;
	std::cout << "|" << std::endl;
}

PhoneBook::PhoneBook(){}

PhoneBook::~PhoneBook(){}

void PhoneBook::add(void)
{
	static int	i;
	Contact	*new = this->contacts[i % N_CONTACTS];

	std::cout << "add\n";
	//std::cout << "> " << std::flush;
	//std::cin >> input;
	i++
}

void PhoneBook::search(void) const
{
	std::cout << "search\n";
	//std::cout << "> " << std::flush;
	//std::cin >> input;
}

void PhoneBook::show(void) const
{
	std::cout << "show\n";
	for (int i = 0; i < N_CONTACTS; i++)
	{
	}
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
