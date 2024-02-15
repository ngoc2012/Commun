/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:17:48 by ngoc              #+#    #+#             */
/*   Updated: 2024/02/15 10:55:58 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream> // Add this line for ifstream
#include <map>

//#include "BitcoinExchange.hpp"

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
        size_t  pos = line.find(" | ");
        if (pos != 10)
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }
        std::cout << "'" << line.substr(0, pos) << "'|'" << std::atoi(line.substr(pos + 3)) << "'" << std::endl;
    }
    
	return (0);
}
