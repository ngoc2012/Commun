/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 08:54:04 by ngoc              #+#    #+#             */
/*   Updated: 2024/02/15 21:55:25 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream> // Add this line for ifstream
#include <algorithm>
#include <climits>  // For INT_MAX
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

static int     binarySearch(std::list<int>& dates, int target, int start, int end) {
    int low = start;
    int high = end;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return high;
}

float   BitcoinExchange::exchange(std::string date, float b)
{
    if (_prices.find(date) == _prices.end())
        throw BitcoinExchange::OutOfDate();
    return (b * _prices[date]);
}

const char* BitcoinExchange::DataError::what() const throw() { return ("Data Error: "); }
const char* BitcoinExchange::OutOfDate::what() const throw() { return ("Error: Data on this date not found."); }
