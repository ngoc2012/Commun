/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:17:48 by ngoc              #+#    #+#             */
/*   Updated: 2024/02/14 17:51:11 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <map>

//#include "Span.hpp"

int	main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: ./btc filename." << std::endl;
        return (1);
    }
    std::ifstream	        f(argv[1]);
	if (!f.is_open())
    {
		std::cerr << "Error: Opening the file." << std::endl;
		return (1);
	}

    std::string     line;
    if (!std::getline(f, line))
    {
		std::cerr << "Error: File empty." << std::endl;
		return (1);
	}
	while (std::getline(f, line))
	{
        std::cout << line << std::endl;
        std::cout << line.find(" | ") << std::endl;
    }
    
	return (0);
}
