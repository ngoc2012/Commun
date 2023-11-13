/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Convert.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/13 09:31:50 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Convert.hpp"

bool	isNumber(const std::string& s) {
	std::istringstream	iss(s);
	double			f;
	iss >> std::noskipws >> f;
	return iss.eof() && !iss.fail();
}

Convert::Convert() {}

Convert::Convert(const Convert& src) { *this = src; }

Convert&	Convert::operator=( Convert const & src )
{
	(void) src;
	return (*this);
}

Convert::~Convert() {}

Convert::Convert(char *n)
{
	_s_char = std::string("impossible");
	_s_int = std::string("impossible");
	_s_float = std::string("impossible");
	_s_double = std::string("impossible");
	if (n[strlen(n) - 1] == 'f')
	{
		type = FLOAT;
		n[strlen(n) - 1] = 0;
		char	*n0 = n;
		if (n[0] == '+' || n[0] == '-')
			n0++;
		if (isNumber(std::string(n0)) == false)
			type = NONE;
	}
	else if (isNumber(std::string(n)) == false)
	{
		if (std::string(n).length() == 1)
			type = CHAR;
		else
			type = NONE;
	}
	else
	{
		if (strchr(n, '.'))
			type = DOUBLE;
		else
			type = INT;
	}
	get_str(n);
}

void	Convert::get_str(char *n)
{
	double	c = atof(n);
	_char = static_cast<char>(c);
	_int = static_cast<int>(c);
	_float = static_cast<float>(c);
	_double = static_cast<double>(c);
	get_char(n);
	/*
	switch (type)
	{
		case CHAR:
			std::cout << "char: "	<< *n << std::endl;
			std::cout << "int: " 	<< _int << std::endl;
			std::cout << "float: "	<< _float << ".0" << std::endl;
			std::cout << "double: "	<< _double << std::endl;
			break;
		case INT:
			_char = *n;
			_int = static_cast<int>(*n);
			_float = static_cast<float>(*n);
			_double = static_cast<double>(*n);
		case FLOAT:
		case DOUBLE:
	}
	*/
}
/*
std::string	cout_value(void *c)
{
	std::ostringstream oss;
	std::streambuf* oldCoutBuffer = std::cout.rdbuf(oss.rdbuf());
	std::cout << *c;
	std::cout.rdbuf(oldCoutBuffer);
	return (oss.str());
}
*/
void     Convert::getChar( char* n )
{
	std::cout << "char: ";
	switch (type)
	{
		case NONE:
			std::cout << "impossible";
			break;
		case CHAR:
			std::cout << *n;
			break;
		case INT:
		case FLOAT:
		case DOUBLE:
			if (_int < 32 || _int > 126)
				std::cout << "Non displayable";
			else
				std::cout << "'" << _int << "'";
			break;
	}
	std::cout << std::endl;
}

/*
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
		|| c < -(std::numeric_limits<int>::max() + 1))
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
		if (oss.str().find('e') == std::string::npos
			&& oss.str().find('.') == std::string::npos)
			std::cout << ".0";
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
		std::cout << "nan";
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
		if (oss.str().find('e') == std::string::npos
			&& oss.str().find('.') == std::string::npos)
			std::cout << ".0";
	}
}
*/
