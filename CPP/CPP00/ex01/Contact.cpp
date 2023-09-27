/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 18:45:45 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/27 09:03:15 by minh-ngu         ###   ########.fr       */
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
	std::cout << "|" << std::setw(WIDTH) << printLen( this->_nickName, WIDTH) << std::flush;
	std::cout << "|" << std::endl;
}

void Contact::show(void) const
{
	std::cout << "First name: " << this->_firstName << std::endl;
	std::cout << "Last name: " << this->_lastName << std::endl;
	std::cout << "Nick name: " << this->_nickName << std::endl;
	std::cout << "Phone number: " << this->_phoneNumber << std::endl;
	std::cout << "Darkest secret: " << this->_darkestSecret << std::endl;
}

#endif
