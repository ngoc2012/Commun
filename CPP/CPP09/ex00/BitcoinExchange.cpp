/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 08:54:04 by ngoc              #+#    #+#             */
/*   Updated: 2024/02/15 14:17:25 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream> // Add this line for ifstream
                   //
#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(const char *data)
{
    std::ifstream	        f(data);
    if (!f.is_open())
    {
        std::cerr << "Error: could not open file." << std::endl;
        throw BitcoinExchange::DataError();
    }
    std::string     line;
    if (!std::getline(f, line))
    {
        std::cerr << "Error: Input file empty." << std::endl;
        throw BitcoinExchange::DataError();
    }
    while (std::getline(f, line))
    {
        size_t  pos = line.find(",");
        if (pos != 10)
        {
            std::cerr << "Error: data form invalid => " << line << std::endl;
            throw BitcoinExchange::DataError();
        }
        b = std::atof(line.substr(pos + 1).c_str());
        date = line.substr(0, pos);
        if (b < 0)
        {
            std::cerr << "Error: not a positive number." << std::endl;
            throw BitcoinExchange::DataError();
        }
    }
}

BitcoinExchange::~BitcoinExchange() {}

float   BitcoinExchange::exchange(std::string date, float b) const
{
    if (_prices.find(date) == _prices.end())
        throw BitcoinExchange::OutOfDate();
    return (b * _prices[date]);
}

const char* BitcoinExchange::DataError::what() const throw() { return ("Error: Data invalid."); }
const char* BitcoinExchange::OutOfDate::what() const throw() { return ("Error: Data this date not found."); }
