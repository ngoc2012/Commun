/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 08:54:04 by ngoc              #+#    #+#             */
/*   Updated: 2024/02/15 22:09:58 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream> // Add this line for ifstream
#include <algorithm>
#include <cstdlib>  // For std::atoi

#include "BitcoinExchange.hpp"

int     date2int(std::string& date)
{
    int     v = std::atoi(date.substr(8, 2).c_str());
    v += std::atoi(date.substr(5, 2).c_str()) * 100;
    v += std::atoi(date.substr(4).c_str()) * 10000;
    return (v);
}

BitcoinExchange::BitcoinExchange(const char *data)
{
    _max_date = 0;
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
    float           b;
    std::string     date;
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
        //std::cout << "'" << date << "'|'" << b << "'" << std::endl;
        _prices.push_back(b);
        _dates.push_back(date2int(date));
    }
}

BitcoinExchange::~BitcoinExchange() {}

static bool    isValidDateFormat(std::string& date)
{
    if (date.length() != 10) {
        return (false);
    }

    for (int i = 0; i < 10; ++i)
    {
        if (i == 4 || i == 7)
        {
            if (date[i] != '-')
                return (false);
        } else {
            if (!isdigit(date[i]))
                return (false);
        }
    }

    return true;
}

static size_t     search(std::list<int>& dates, int target)
{
    size_t     pos = 0;
    std::list<int>::iterator it;
    while (it != dates.end())
    {
        if (*it > date)
            return (pos);
        it++;
    }
    if (it == dates.end())
        return (_dates.size() - 1);
}

float   BitcoinExchange::exchange(std::string date, float b)
{
    size_t pos = search(_dates, date2int(date));
    std::list<int>::iterator it;
    it = _prices.begin() + pos;
    return (b * (*it));
}

const char* BitcoinExchange::DataError::what() const throw() { return ("Data Error: "); }
const char* BitcoinExchange::OutOfDate::what() const throw() { return ("Error: Data on this date not found."); }
