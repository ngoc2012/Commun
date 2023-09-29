/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 18:45:45 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/29 10:02:22 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_H
# define PHONEBOOK_H

# define WIDTH 10

#include "Contact.hpp"

std::string printLen(std::string str, int len) {
	if ((int) str.length() > len)
		return str.substr(0, len - 1) + ".";
	return str;
}

Contact::Contact(){}

Contact::~Contact(){}

void Contact::show_table(int index) const
{
	std::cout << "|" << std::setw(WIDTH) << index << std::flush;
	std::cout << "|" << std::setw(WIDTH) << printLen(_firstName, WIDTH) << std::flush;
	std::cout << "|" << std::setw(WIDTH) << printLen( _lastName, WIDTH) << std::flush;
	std::cout << "|" << std::setw(WIDTH) << printLen( _nickName, WIDTH) << std::flush;
	std::cout << "|" << std::endl;
}

void Contact::show(void) const
{
	std::cout << "First name: " << _firstName << std::endl;
	std::cout << "Last name: " << _lastName << std::endl;
	std::cout << "Nick name: " << _nickName << std::endl;
	std::cout << "Phone number: " << _phoneNumber << std::endl;
	std::cout << "Darkest secret: " << _darkestSecret << std::endl;
}

void	Contact::set_firstName(std::string str)
{
	_firstName = str;
}

void 	Contact::set_lastName(std::string str)
{
	_lastName = str;
}

void 	Contact::set_nickName(std::string str)
{
	_nickName = str;
}

void 	Contact::set_phoneNumber(std::string str)
{
	_phoneNumber = str;
}

void 	Contact::set_darkestSecret(std::string str)
{
	_darkestSecret = str;
}

#endif
