/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Convert.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/03 18:32:24 by ngoc             ###   ########.fr       */
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

bool	isNumber(const std::string& s) {
	std::istringstream	iss(s);
	double			f;
	iss >> std::noskipws >> f;
	return iss.eof() && !iss.fail();
}

void     Convert::getChar( char* n )
{
	double	c = atof(n);
	if (isNumber(std::string(n)) == false
		|| c < 32 || c > 126)
		std::cout << "nan";
	else
		std::cout << static_cast<char>(c);
}

void     Convert::getInt( char* n )
{
	double	c = atof(n);
	if (isNumber(std::string(n)) == false
		|| c < std::numeric_limits<int>::min()
		|| c > std::numeric_limits<int>::max())
		std::cout << "nan";
	else
		std::cout << static_cast<int>(c);
}

void     Convert::getFloat( char* n )
{
	double	c = atof(n);
	if (isNumber(std::string(n)) == false)
		std::cout << "nanf";
	else if (c < std::numeric_limits<float>::min())
		std::cout << "-inff";
	else if (c > std::numeric_limits<float>::max())
		std::cout << "+inff";
	else
		std::cout << static_cast<float>(c);
}

void     Convert::getDouble( char* n )
{
	double	c = atof(n);
	if (isNumber(std::string(n)) == false)
		std::cout << "nan";
	else if (c == std::numeric_limits<double>::min())
		std::cout << "-inf";
	else if (c == std::numeric_limits<double>::max())
		std::cout << "+inf";
	else
		std::cout << c;
}
