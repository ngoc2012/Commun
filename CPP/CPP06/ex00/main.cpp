/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:17:48 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/03 08:54:38 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Convert.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Usage: convert [0..1]" << std::endl;
		return (1);
	}
	Convert		c;
	std::cout << "char  : " << c.getChar(argv[1])	<< std::endl;
	std::cout << "int   : " << c.getInt(argv[1])	<< std::endl;
	std::cout << "float : " << c.getFloat(argv[1])  << std::endl;
	std::cout << "double: " << c.getDouble(argv[1]) << std::endl;
	return (0);
}
