/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Convert.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/03 11:26:32 by ngoc             ###   ########.fr       */
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

void     Convert::getChar( char* n )
{
	char	c;
	c = static_cast<char>(atof(n));
	if (c == std::numeric_limits<char>::quiet_NaN())
		std::cout << "nan";
	else
		std::cout << c;
}

void     Convert::getInt( char* n )
{
	int	c;
	c = static_cast<int>(atof(n));
	std::cout << c;
}

void     Convert::getFloat( char* n )
{
	float	c;
	c = static_cast<float>(atof(n));
	std::cout << c;
}

void     Convert::getDouble( char* n )
{
	double	c;
	c = atof(n);
	std::cout << c;
}
