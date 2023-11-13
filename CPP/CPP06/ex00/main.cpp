/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:17:48 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/13 09:21:05 by ngoc             ###   ########.fr       */
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

	std::stringstream ss(argv[1]);
	long double ld;
	ss >> ld;

	Convert		c(argv[1]);
/*
	Convert		c;
	//double	flt_max = atof("340282346638528859811704183484516925440");
	//int	i = 0;
	//while (flt_max++ <= std::numeric_limits<float>::max())
	//	i++;
	//std::cout << i << std::endl;
	std::cout << "atof: " << atof(argv[1]) << std::endl;
	std::cout << "char: "; c.getChar(argv[1]);	std::cout << std::endl;
	std::cout << "int: "; c.getInt(argv[1]);	std::cout << std::endl;
	std::cout << "float: "; c.getFloat(argv[1]);	std::cout << std::endl;
	std::cout << "double: "; c.getDouble(argv[1]);	std::cout << std::endl;
	*/
	return (0);
}
