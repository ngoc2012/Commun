/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 08:54:04 by ngoc              #+#    #+#             */
/*   Updated: 2024/02/16 09:34:35 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream> // Add this line for ifstream
#include <algorithm>
#include <cstdlib>  // For std::atoi

#include "RPN.hpp"

RPN::RPN(const char *data)
{
    _max_date = 0;
    std::ifstream	        f(data);
    if (!f.is_open())
    {
        std::cerr << "Error: could not open file." << std::endl;
        throw RPN::DataError();
    }
    std::string     line;
    if (!std::getline(f, line))
    {
        std::cerr << "Error: Input file empty." << std::endl;
        throw RPN::DataError();
    }
    float           b;
    std::string     date;
    while (std::getline(f, line))
    {
        size_t  pos = line.find(",");
        if (pos != 10)
        {
            std::cerr << "Error: data form invalid => " << line << std::endl;
            throw RPN::DataError();
        }
        b = std::atof(line.substr(pos + 1).c_str());
        date = line.substr(0, pos);
        if (b < 0)
        {
            std::cerr << "Error: not a positive number." << std::endl;
            throw RPN::DataError();
        }
        //std::cout << "'" << date << "'|'" << b << "'" << std::endl;
        _prices.push_back(b);
        _dates.push_back(date2int(date));
    }
}

RPN::~RPN() {}

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

float   RPN::exchange(std::string date, float b)
{
    if (!isValidDateFormat(date))
        throw RPN::DateError();
    return (b * search(_dates, _prices, date2int(date)));
}

const char* RPN::DataError::what() const throw() { return ("Data Error: "); }
const char* RPN::DateError::what() const throw() { return ("Error: Date error."); }
