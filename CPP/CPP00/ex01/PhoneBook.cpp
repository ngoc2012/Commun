/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 18:45:45 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/27 06:38:35 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

PhoneBook::PhoneBook(){}

PhoneBook::~PhoneBook(){}

std::string	get_field(void)
{
	std::string	input = "";
	while (input.compare("")) {
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
