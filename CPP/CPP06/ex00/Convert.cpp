/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Convert.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/13 11:52:19 by ngoc             ###   ########.fr       */
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
	while (*n == '0' && *(n + 1))
		n++;
	std::cout << "strlen: " << std::string(n).length() << std::endl;
	if (std::string(n).length() > 405)
		type = NONE;
	else if (n[strlen(n) - 1] == 'f')
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
	if (type == CHAR)
		_char = *n;
	else
		_char = static_cast<char>(c);
	_int = static_cast<int>(c);
	_float = static_cast<float>(c);
	_double = static_cast<double>(c);
	std::string data = std::string(n);
	std::stringstream ss(data);
	long double _ldouble;
	ss >> _ldouble;
	std::cout << "long double: " << _ldouble << std::endl;
	get_char();
	get_int(n);
	get_float(n);
	get_double(n);
}

void     Convert::get_char()
{
	std::cout << "char: ";
	switch (type)
	{
		case NONE:
			std::cout << "impossible";
			break;
		case CHAR:
			std::cout << "'" << _char << "'";
			break;
		case INT:
		case FLOAT:
		case DOUBLE:
			if (_int < 32 || _int > 126)
				std::cout << "Non displayable";
			else
				std::cout << "'" << _char << "'";
			break;
	}
	std::cout << std::endl;
}

void     Convert::get_int( char* n )
{
	std::string s = std::string(n);
	std::cout << "int: ";
	if (s == "-inf" || s == "-inff")
		std::cout << "-inf";
	else if (s == "+inf" || s == "+inff")
		std::cout << "+inf";
	else if (_double > std::numeric_limits<int>::max()
		|| _double < -(std::numeric_limits<int>::max() + 1))
		std::cout << "impossible";
	else
	{
		switch (type)
		{
			case NONE:
			case CHAR:
				std::cout << "impossible";
				break;
			case INT:
			case FLOAT:
			case DOUBLE:
				std::cout << _int;
				break;
		}
	}
	std::cout << std::endl;
}

void     Convert::get_float( char* n )
{
	std::string s = std::string(n);
	std::cout << "float: ";
	if (s == "-inf" || s == "-inff")
		std::cout << "-inff";
	else if (s == "+inf" || s == "+inff")
		std::cout << "+inff";
	else if (s == "nan" || s == "nanf")
		std::cout << "nanf";
	else if ((_double > 0 && _double < std::numeric_limits<float>::min())
		|| (_double < 0 && _double > -std::numeric_limits<float>::min())
		|| _double > std::numeric_limits<float>::max()
		|| _double < -std::numeric_limits<float>::max())
		std::cout << "impossible";
	else
	{
		switch (type)
		{
			case NONE:
			case CHAR:
				std::cout << "impossible";
				break;
			case INT:
			case FLOAT:
			case DOUBLE:
				std::ostringstream oss;
				std::streambuf* oldCoutBuffer = std::cout.rdbuf(oss.rdbuf());
				std::cout << _float;
				std::cout.rdbuf(oldCoutBuffer);
				std::cout << oss.str();
				if (oss.str().find('e') == std::string::npos
						&& oss.str().find('.') == std::string::npos)
					std::cout << ".0";
				std::cout << "f";
				break;
		}
	}
	std::cout << std::endl;
}
void     Convert::get_double( char* n )
{
	std::string s = std::string(n);
	std::cout << "double: ";
	if (s == "-inf" || s == "-inff")
		std::cout << "-inff";
	else if (s == "+inf" || s == "+inff")
		std::cout << "+inff";
	else if (s == "nan" || s == "nanf")
		std::cout << "nan";
	else if ((_double > 0 && _double < std::numeric_limits<double>::min())
		|| (_double < 0 && _double > -std::numeric_limits<double>::min())
		|| _double > std::numeric_limits<double>::max()
		|| _double < -std::numeric_limits<double>::max())
		std::cout << "impossible1";
	else
	{
		switch (type)
		{
			case NONE:
			case CHAR:
				std::cout << "impossible2";
				break;
			case INT:
			case FLOAT:
			case DOUBLE:
				std::ostringstream oss;
				std::streambuf* oldCoutBuffer = std::cout.rdbuf(oss.rdbuf());
				std::cout << _double;
				std::cout.rdbuf(oldCoutBuffer);
				std::cout << oss.str();
				if (oss.str().find('e') == std::string::npos
						&& oss.str().find('.') == std::string::npos)
					std::cout << ".0";
				break;
		}
	}
	std::cout << std::endl;
}
