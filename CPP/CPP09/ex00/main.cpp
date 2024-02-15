/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:17:48 by ngoc              #+#    #+#             */
/*   Updated: 2024/02/15 14:25:46 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream> // Add this line for ifstream
#include <algorithm>
#include <map>

#include "BitcoinExchange.hpp"

int	main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: ./btc filename" << std::endl;
        return (1);
    }
    std::ifstream	        f(argv[1]);
    if (!f.is_open())
    {
        std::cerr << "Error: could not open file." << std::endl;
        return (1);
    }

    std::string     line;
    if (!std::getline(f, line))
    {
        std::cerr << "Error: Input file empty." << std::endl;
        return (1);
    }
    
    BitcoinExchange*    ex;
    try
    {
        BitcoinExchange ex0("data.csv");
        ex = &ex0;
    }
    catch (std::exception & e)
    {
        std::cerr << e.what() << std::endl;
        return (1);
    }

    float           b;
    float           p;
    std::string     date;
    while (std::getline(f, line))
    {
        size_t  pos = line.find(" | ");
        if (pos != 10)
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }
        b = std::atof(line.substr(pos + 3).c_str());
        date = line.substr(0, pos);
        if (b < 0)
        {
            std::cerr << "Error: not a positive number." << std::endl;
            continue;
        }
        if (b > 1000)
        {
            std::cerr << "Error: too large a number." << std::endl;
            continue;
        }
        //std::cout << "'" << date << "'|'" << b << "'" << std::endl;
        try
        {
            p = ex->exchange(date, b);
        }
        catch (std::exception & e)
        {
            std::cerr << e.what() << " => " << line << std::endl;
            continue;
        }
        std::cout << date << " => " << b << " = " << p << std::endl;
    }
    
	return (0);
}
