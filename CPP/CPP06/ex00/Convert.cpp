/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Convert.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/04 10:58:40 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Convert.hpp"

Convert::Convert() {}

Convert::Convert(const Convert& src) { *this = src; }

Convert&	Convert::operator=( Convert const & src )
{
	(void) src;
	return (*this);
}

Convert::~Convert() {}

bool	isNumber(const std::string& s) {
	std::istringstream	iss(s);
	double			f;
	iss >> std::noskipws >> f;
	return iss.eof() && !iss.fail();
}

void     Convert::getChar( char* n )
{
	double	c = atof(n);
	if (isNumber(std::string(n)) == false)
	{
		if (std::string(n).length() == 1)
			std::cout << "'" << n << "'";
		else
			std::cout << "impossible";
	}
	else if (c < 32 || c > 126)
		std::cout << "Non displayable";
	else
		std::cout << "'" << static_cast<char>(c) << "'";
}

void     Convert::getInt( char* n )
{
	switch (std::string(n))
	{
		case "-inf":
		case "-inff":
			std::cout << "-inf";
			return ;
		case "+inf":
		case "+inff":
			std::cout << "+inf";
			return ;
		default:
	}
	double	c = atof(n);
	if (isNumber(std::string(n)) == false
		|| c < std::numeric_limits<int>::min()
		|| c > std::numeric_limits<int>::max())
		std::cout << "impossible";
	else
		std::cout << static_cast<int>(c);
}

void     Convert::getFloat( char* n )
{
	double	c = atof(n);
	std::cout << std::numeric_limits<float>::max() << "===";
	if (isNumber(std::string(n)) == false)
		std::cout << "nanf";
	else if (c < std::numeric_limits<float>::min())
		std::cout << "-inff";
	else if (c > std::numeric_limits<float>::max())
		std::cout << "+inff";
	else
		std::cout << static_cast<float>(c) << "f";
}

void     Convert::getDouble( char* n )
{
	double	c = atof(n);
	std::cout << std::numeric_limits<double>::max() << "===";
	if (isNumber(std::string(n)) == false)
		std::cout << "nan";
	else if (c == std::numeric_limits<double>::min())
		std::cout << "-inf";
	else if (c == std::numeric_limits<double>::max())
		std::cout << "+inf";
	else
		std::cout << c;
}
