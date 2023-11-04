/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Convert.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/04 12:40:05 by ngoc             ###   ########.fr       */
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
	if (n[strlen(n) - 1] == 'f')
		n[strlen(n) - 1] = 0;
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

//https://en.cppreference.com/w/cpp/types/numeric_limits
void     Convert::getInt( char* n )
{
	if (n[strlen(n) - 1] == 'f')
		n[strlen(n) - 1] = 0;
	double	c = atof(n);
	std::string s = std::string(n);
	if (s == "-inf" || s == "-inff")
		std::cout << "-inf";
	else if (s == "+inf" || s == "+inff")
		std::cout << "+inf";
	else if (isNumber(std::string(n)) == false
		|| c > std::numeric_limits<int>::max()
		|| c < -std::numeric_limits<int>::max())
		std::cout << "impossible";
	else
		std::cout << static_cast<int>(c);
}

void     Convert::getFloat( char* n )
{
	if (n[strlen(n) - 1] == 'f')
		n[strlen(n) - 1] = 0;
	double	c = atof(n);
	std::string s = std::string(n);
	if (s == "-inf" || s == "-inff")
		std::cout << "-inff";
	else if (s == "+inf" || s == "+inff")
		std::cout << "+inff";
	else if (s == "nan" || s == "nanf")
		std::cout << "nanf";
	else if (isNumber(std::string(n)) == false
		|| (c > 0 && c < std::numeric_limits<float>::min())
		|| (c < 0 && c > -std::numeric_limits<float>::min())
		|| c > std::numeric_limits<float>::max()
		|| c < -std::numeric_limits<float>::max())
		std::cout << "impossible";
	else
	{
		std::ostringstream oss;
		std::streambuf* oldCoutBuffer = std::cout.rdbuf(oss.rdbuf());
		std::cout << static_cast<float>(c);
		std::cout.rdbuf(oldCoutBuffer);
		std::cout << oss.str();
		std::cout << "f";
	}
}

void     Convert::getDouble( char* n )
{
	if (n[strlen(n) - 1] == 'f')
		n[strlen(n) - 1] = 0;
	double	c = atof(n);
	std::string s = std::string(n);
	if (s == "-inf" || s == "-inff")
		std::cout << "-inff";
	else if (s == "+inf" || s == "+inff")
		std::cout << "+inff";
	else if (s == "nan" || s == "nanf")
		std::cout << "nanf";
	else if (isNumber(std::string(n)) == false
		|| (c > 0 && c < std::numeric_limits<double>::min())
		|| (c < 0 && c > -std::numeric_limits<double>::min())
		|| c > std::numeric_limits<double>::max()
		|| c < -std::numeric_limits<double>::max())
		std::cout << "impossible";
	else
	{
		std::ostringstream oss;
		std::streambuf* oldCoutBuffer = std::cout.rdbuf(oss.rdbuf());
		std::cout << static_cast<double>(c);
		std::cout.rdbuf(oldCoutBuffer);
		std::cout << oss.str();
	}
}
