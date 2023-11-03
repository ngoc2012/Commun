/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Convert.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/03 09:03:55 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Convert.hpp"

Convert::Convert() {std::cout << "Convert default constructor." << std::endl;}

Convert::Convert(const Convert& src) {
	*this = src;
	std::cout << "Convert copy constructor." << std::endl;
}

Convert&	Convert::operator=( Convert const & src )
{
	type = src.type;
	return (*this);
}

Convert::~Convert() { std::cout << "Convert destructor." << std::endl; }

std::string     Convert::getChar( std::string n )
{
	char	c;
	c = stoi(n);
	return (std::string(c));
}

std::string     Convert::getChar( std::string n )
{
	char	c;
	c = stoi(n);
}
