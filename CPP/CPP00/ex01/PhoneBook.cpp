/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 18:45:45 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/27 09:23:34 by minh-ngu         ###   ########.fr       */
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

std::string	get_field(std::string str)
{
	std::string	input = "";

	while (emptyEntry(input)) {
		std::cout << str;
		std::cout << "> " << std::flush;
		std::cin >> input;
	}
	return (input);
}

void	PhoneBook::add(void)
{
	static int	i;
	Contact		*new_contact = &this->contacts[i % N_CONTACTS];

	new_contact->_firstName = get_field("First name: "); 
	new_contact->_lastName = get_field("Last name: "); 
	new_contact->_nickName = get_field("Nick name: "); 
	new_contact->_phoneNumber = get_field("Phone number: "); 
	new_contact->_darkestSecret = get_field("Darkest secret: "); 
	i++;
}

void	PhoneBook::show(void) const
{
	std::cout << "---------------------------------------------\n";
	std::cout << "|     Index|First Name| Last Name| Nick Name|\n";
	std::cout << "---------------------------------------------\n";
	for (int i = 0; i < N_CONTACTS; i++)
		this->contacts[i].show_table(i + 1);
	std::cout << "---------------------------------------------\n";
}

void	PhoneBook::search(void) const
{
	std::string	input;

	this->show();
	std::cout << "Contact id ?\n";
	std::cout << "> " << std::flush;
	std::cin >> input;

	int	i = atoi(input.c_str());
	if (i < 1 || i > 8)
	{
		std::cerr << "Contact id invalid\n";
		return ;
	}
	this->contacts[i - 1].show();
}
