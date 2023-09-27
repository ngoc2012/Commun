/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 18:45:45 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/27 12:39:55 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib> // for atoi
#include <cstring> // for c_str()
#include <limits> // numeric_limits
#include "PhoneBook.hpp"

PhoneBook::PhoneBook(){}

PhoneBook::~PhoneBook(){}

bool	emptyEntry(const std::string& str) {

	int	i = -1;

	while (str[++i]) {
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n') {
			return false;
		}
	}
	return true;
}

std::string	get_field0(std::string str)
{
	std::string	input;
	std::string	out = "";

	std::cout << str << std::flush;
	while (std::cin >> input)
	{
		if (!input.empty())
			return (input);
	}
	if (std::cin.eof())
	{
		std::cin.clear();  // Clear the EOF state
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return (out);
	}
	if (emptyEntry(input))
		return (out);
	return (input);
}

std::string	get_field(std::string str)
{
	std::string	input;
	bool		valid = false;

	do
	{
		std::cout << str << std::flush;
		std::cin >> input;
		if (std::cin.good() && (input >= 0 && input <= 8)) {
			valid = true;
		} else {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
			std::cout << "Invalid index; please re-enter." << std::endl;
		}
	} while (!valid);
	return (input);
}

void	PhoneBook::add(void)
{
	static int	i;
	Contact		*new_contact = &this->contacts[i % N_CONTACTS];

	new_contact->set_firstName(get_field("First name: ")); 
	new_contact->set_lastName(get_field("Last name: ")); 
	new_contact->set_nickName(get_field("Nick name: ")); 
	new_contact->set_phoneNumber(get_field("Phone number: ")); 
	new_contact->set_darkestSecret(get_field("Darkest secret: ")); 
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
	input = get_field("Contact id: "); 

	int	i = atoi(input.c_str());
	if (i < 1 || i > N_CONTACTS)
	{
		std::cerr << "Contact id invalid\n";
		return ;
	}
	this->contacts[i - 1].show();
}
