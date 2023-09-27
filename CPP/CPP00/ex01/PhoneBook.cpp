/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 18:45:45 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/27 13:55:49 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib> // for atoi
#include <cstring> // for c_str()
#include <limits> // numeric_limits
#include "PhoneBook.hpp"

PhoneBook::PhoneBook()
{
	this->n = 0;
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
	Contact		*new_contact = &this->contacts[i % N_CONTACTS];
	std::string	phoneNumber;

	new_contact->set_firstName(get_field("First name: ")); 
	new_contact->set_lastName(get_field("Last name: ")); 
	new_contact->set_nickName(get_field("Nick name: ")); 
	do
	{
		phoneNumber = get_field("Phone number: ");
		if (!isdigits(phoneNumber))
			std::cout << "Error: Not a number\n";
	} while (!isdigits(phoneNumber));
	new_contact->set_phoneNumber(phoneNumber); 

	new_contact->set_darkestSecret(get_field("Darkest secret: ")); 
	if (this->get_n() < 8)
		this->set_n(this->get_n() + 1);
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
	if (i < 1 || i > this->get_n())
	{
		std::cerr << "Contact id invalid\n";
		return ;
	}
	this->contacts[i - 1].show();
}

void	PhoneBook::set_n(int n)
{
	this->n = n;
}

int	PhoneBook::get_n(void) const
{
	return (this->n);
}
