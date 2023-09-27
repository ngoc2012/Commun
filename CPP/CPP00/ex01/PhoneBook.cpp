/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 18:45:45 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/27 08:46:10 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"
//#include <cstdlib> // for atoi
#include <cstdlib> // for atoi
#include <cstring> // for c_str()

PhoneBook::PhoneBook(){}

PhoneBook::~PhoneBook(){}

bool	emptyEntry(const std::string& str) {

	int	i = -1;

	while (str[++i]) {
		if (str[i] != ' ' && str[i] != '\t') {
			return false;
		}
	}
	return true;
}

std::string	get_field(void)
{
	std::string	input = "";

	while (emptyEntry(input)) {
		std::cout << "> " << std::flush;
		std::cin >> input;
	}
	return (input);
}

void PhoneBook::add(void)
{
	//static int	i;
	//Contact	*new_contact = &this->contacts[i % N_CONTACTS];

	std::cout << "add\n";
	//std::cout << "> " << std::flush;
	//std::cin >> input;
	//i++;
}

void PhoneBook::search(void) const
{
	std::string	input;
	std::cout << "Contact id ?\n";
	std::cout << "> " << std::flush;
	std::cin >> input;
	int	num = std::stoi(input);
	if (num < 1 || num > 8)
		std::cerr << "Contact id invalid\n";
}

void PhoneBook::show(void) const
{
	std::cout << "---------------------------------------------\n";
	std::cout << "|     Index|First Name| Last Name| Nick Name|\n";
	std::cout << "---------------------------------------------\n";
	for (int i = 0; i < N_CONTACTS; i++)
		this->contacts[i].show(i + 1);
	std::cout << "---------------------------------------------\n";
}
