/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 18:45:45 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/27 08:58:08 by minh-ngu         ###   ########.fr       */
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
	std::cout << "|" << std::setw(WIDTH) << printLen(this->_firstName, WIDTH) << std::flush;
	std::cout << "|" << std::setw(WIDTH) << printLen( this->_lastName, WIDTH) << std::flush;
	std::cout << "|" << std::setw(WIDTH) << printLen( this->_nickname, WIDTH) << std::flush;
	std::cout << "|" << std::endl;
}

void Contact::show(int index) const
{
		std::string _firstName;
		std::string _lastName;
		std::string _nickname;
		std::string _phoneNumber;
		std::string _darkestSecret;
	std::cout << "|" << std::setw(WIDTH) << index << std::flush;
	std::cout << "|" << std::setw(WIDTH) << printLen(this->_firstName, WIDTH) << std::flush;
	std::cout << "|" << std::setw(WIDTH) << printLen( this->_lastName, WIDTH) << std::flush;
	std::cout << "|" << std::setw(WIDTH) << printLen( this->_nickname, WIDTH) << std::flush;
	std::cout << "|" << std::endl;
}

#endif
