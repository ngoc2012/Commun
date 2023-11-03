/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Convert.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/03 11:17:24 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Convert.hpp"

Convert::Convert()
{
	std::cout << "Convert default constructor." << std::endl;
}

Convert::Convert(const Convert& src) {
	*this = src;
	std::cout << "Convert copy constructor." << std::endl;
}

Convert&	Convert::operator=( Convert const & src )
{
	(void) src;
	return (*this);
}

Convert::~Convert() { std::cout << "Convert destructor." << std::endl; }

void     Convert::getChar( std::string n )
{
	char	c;
	std::cout << "atof: " << atof(n.c_str()) << std::endl;
	c = static_cast<char>(atof(n.c_str()));
	std::cout << c;
}

void     Convert::getInt( std::string n )
{
	int	c;
	c = static_cast<int>(atof(n.c_str()));
	std::cout << c;
}

void     Convert::getFloat( std::string n )
{
	float	c;
	c = static_cast<int>(atof(n.c_str()));
	std::cout << c;
}

void     Convert::getDouble( std::string n )
{
	double	c;
	c = atof(n.c_str());
	std::cout << c;
}
