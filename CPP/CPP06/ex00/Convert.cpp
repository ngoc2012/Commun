/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Convert.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/03 13:11:46 by ngoc             ###   ########.fr       */
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
	if (atof(str) == std::numeric_limits<double>::quiet_NaN())
		std::cout << "nan";
	int	ni = static_cast<int>(atof(n));
	if (ni >= std::numeric_limits<char>::min()
		&& ni <= std::numeric_limits<char>::max()
		&& ni >= 32 && ni <= 126)
		std::cout << static_cast<char>(atof(n));
	else
		std::cout << "nan";
}

void     Convert::getInt( char* n )
{
	if (atof(str) == std::numeric_limits<double>::quiet_NaN())
		std::cout << "nan";
	float	c;
	c = static_cast<float>(atof(n));
	if (c >= std::numeric_limits<int>::min()
		&& c <= std::numeric_limits<int>::max())
		std::cout << c;
	else
		std::cout << "nan";
}

void     Convert::getFloat( char* n )
{
	if (atof(str) == std::numeric_limits<double>::quiet_NaN())
		std::cout << "nanf";
	double	c;
	c = static_cast<double>(atof(n));
	if (c >= std::numeric_limits<float>::min()
		&& c <= std::numeric_limits<float>::max())
		std::cout << c;
	else if (c < std::numeric_limits<float>::min())
		std::cout << "-inff";
	else
		std::cout << "+inff";
}

void     Convert::getDouble( char* n )
{
	if (atof(str) == std::numeric_limits<double>::quiet_NaN())
		std::cout << "nanf";
	double	c;
	c = atof(n);
	std::cout << c;
}
