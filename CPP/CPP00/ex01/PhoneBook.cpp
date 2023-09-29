/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 18:45:45 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/29 10:06:35 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib> // for atoi
#include <cstring> // for c_str()
#include <limits> // numeric_limits
#include "PhoneBook.hpp"

//PhoneBook::PhoneBook() : n(0) {}
PhoneBook::PhoneBook()
{
	n = 0;
}

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

std::string	get_field(std::string str)
{
	std::string	input = "";

	do
	{
		std::cout << str;
		std::getline(std::cin, input);
		if (std::cin.eof())
			exit(1);
	}
	while (input.empty() || emptyEntry(input));
	return (input);
}

bool	isdigits(const std::string& str) {
	int	i;

	i = -1;
	while (str[++i]) {
		if (!std::isdigit(str[i]) && str[i] != ' ') {
			return false;
		}
	}
	return true;
}

void	PhoneBook::add(void)
{
	static int	i;
	Contact		*new_contact = &contacts[i % N_CONTACTS];
	std::string	phoneNumber;

	new_contact->set_firstName(get_field("First name: ")); 
	new_contact->set_lastName(get_field("Last name: ")); 
	new_contact->set_nickName(get_field("Nick name: ")); 
	do
	{
		phoneNumber = get_field("Phone number: ");
		if (!isdigits(phoneNumber))
			std::cerr << "Error: Not a number\n";
	} while (!isdigits(phoneNumber));
	new_contact->set_phoneNumber(phoneNumber); 

	new_contact->set_darkestSecret(get_field("Darkest secret: ")); 
	if (get_n() < 8)
		set_n(get_n() + 1);
	i++;
}

void	PhoneBook::show(void) const
{
	std::cout << "---------------------------------------------\n";
	std::cout << "|     Index|First Name| Last Name| Nick Name|\n";
	std::cout << "---------------------------------------------\n";
	for (int i = 0; i < N_CONTACTS; i++)
		contacts[i].show_table(i + 1);
	std::cout << "---------------------------------------------\n";
}

void	PhoneBook::search(void) const
{
	std::string	input;

	show();
	input = get_field("Contact id: "); 

	int	i = atoi(input.c_str());
	if (i < 1 || i > get_n())
	{
		std::cerr << "Error: Contact id invalid\n";
		return ;
	}
	contacts[i - 1].show();
}

void	PhoneBook::set_n(int n)
{
	n = n;
}

int	PhoneBook::get_n(void) const
{
	return (n);
}
