/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Convert.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/03 09:13:43 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Convert.hpp"

Convert::Convert()
{
	fb = 0;
	fp = 0;
	std::cout << "Convert default constructor." << std::endl;
}

Convert::Convert(const Convert& src) {
	*this = src;
	std::cout << "Convert copy constructor." << std::endl;
}

Convert&	Convert::operator=( Convert const & src )
{
	fp = src.fp;
	fb = src.fb;
	return (*this);
}

Convert::~Convert() { std::cout << "Convert destructor." << std::endl; }

void     Convert::getChar( std::string n )
{
	char	c;
	c = stoi(n);
	std::cout << c;
}

void     Convert::getInt( std::string n )
{
	int	c;
	c = stoi(n);
	std::cout << c;
}

void     Convert::getFloat( std::string n )
{
	float	c;
	c = stof(n);
	std::cout << c;
}

void     Convert::getDouble( std::string n )
{
	double	c;
	c = stod(n);
	std::cout << c;
}
