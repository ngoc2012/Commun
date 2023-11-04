/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:17:48 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/04 13:46:05 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Convert.hpp"

#include <cmath>
#include <cfloat>

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Usage: convert [0..1]" << std::endl;
		return (1);
	}

	int exponent;
	double fraction = std::frexp(FLT_MIN, &exponent);
	double min_value = fraction * std::pow(2, exponent - 1);
	std::cout << "FLT_MIN without exponent: " << min_value << std::endl;

	Convert		c;
	std::cout << "atof: " << atof(argv[1]) << std::endl;
	std::cout << "char: "; c.getChar(argv[1]);	std::cout << std::endl;
	std::cout << "int: "; c.getInt(argv[1]);	std::cout << std::endl;
	std::cout << "float: "; c.getFloat(argv[1]);	std::cout << std::endl;
	std::cout << "double: "; c.getDouble(argv[1]);	std::cout << std::endl;
	return (0);
}
