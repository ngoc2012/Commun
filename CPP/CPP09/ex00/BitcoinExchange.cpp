/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 08:54:04 by ngoc              #+#    #+#             */
/*   Updated: 2024/02/15 12:00:48 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(const char *data)
{
    std::ifstream	        f(data);
    if (!f.is_open())
    {
        std::cerr << "Error: could not open file." << std::endl;
        throw DataError;
    }
    std::string     line;
    if (!std::getline(f, line))
    {
        std::cerr << "Error: Input file empty." << std::endl;
        throw DataError;
    }
    while (std::getline(f, line))
    {
        size_t  pos = line.find(",");
        if (pos != 10)
        {
            std::cerr << "Error: data form invalid => " << line << std::endl;
            continue;
        }
    }
}

BitcoinExchange::~BitcoinExchange() {}

float   BitcoinExchange::exchange(std::string date, float b) const
{
    if (_prices.find(date) == _prices.end())
        throw DataError;
    return (b * _prices[date]);
}

const char* BitcoinExchange::DataError::what() const throw() { return ("Error: Data invalid."); }
const char* BitcoinExchange::OutOfDate::what() const throw() { return ("Error: Data this date not found."); }
