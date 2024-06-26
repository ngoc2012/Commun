/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 08:54:04 by ngoc              #+#    #+#             */
/*   Updated: 2024/02/16 09:08:18 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream> // Add this line for ifstream
#include <algorithm>
#include <cstdlib>  // For std::atoi
#include <cstring>

#include "BitcoinExchange.hpp"

static double     date2int(std::string& date)
{
    double     v = std::atoi(date.substr(8, 2).c_str());
    v += std::atoi(date.substr(5, 2).c_str()) * 100;
    v += std::atoi(date.substr(0, 4).c_str()) * 10000;
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
    const char*     number;
    while (std::getline(f, line))
    {
        size_t  pos = line.find(",");
        if (pos != 10)
        {
            std::cerr << "Error: data form invalid => " << line << std::endl;
            throw BitcoinExchange::DataError();
        }
        date = line.substr(0, pos);
        if (!isValidDateFormat(date))
        {
            std::cerr << "Error: invalid date format: " << date << std::endl;
            throw BitcoinExchange::DataError();
        }
        number = line.substr(pos + 1).c_str();
        if (!isValidNumber(number))
        {
            std::cerr << "Error: not a number: " << number << std::endl;
            throw BitcoinExchange::DataError();
        }
        b = std::atof(number);
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

bool    BitcoinExchange::isValidDateFormat(std::string& date)
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

bool    BitcoinExchange::isValidNumber(const char* str) {
    if (std::strlen(str) == 0) {
        return false;
    }

    char* endptr;
    std::strtol(str, &endptr, 10);
    if (*endptr == '\0') {
        return true;
    }

    std::strtod(str, &endptr);
    if (*endptr == '\0') {
        return true;
    }

    return false;
}

static float     search(std::list<double>& dates, std::list<float>& prices, int date)
{
    std::list<double>::iterator it = dates.begin();
    std::list<float>::iterator itp = prices.begin();
    while (it != dates.end() && *it <= date)
    {
        it++;
        itp++;
    }
    if (itp != prices.begin())
        itp--;
    return (*itp);
}

float   BitcoinExchange::exchange(std::string date, float b)
{
    if (!isValidDateFormat(date))
        throw BitcoinExchange::DateError();
    return (b * search(_dates, _prices, date2int(date)));
}

const char* BitcoinExchange::DataError::what() const throw() { return ("Data Error "); }
const char* BitcoinExchange::DateError::what() const throw() { return ("Error: Date error."); }
