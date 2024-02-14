/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 08:54:04 by ngoc              #+#    #+#             */
/*   Updated: 2024/02/14 15:55:32 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(unsigned int const & n): _N(n) {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& s)
{
    *this = s;
}

BitcoinExchange&	BitcoinExchange::operator=( const BitcoinExchange& s )
{
    for (unsigned int i = 0; i < s._N; i++)
        this->addNumber(s._v[i]);
    return (*this);
}

BitcoinExchange::~BitcoinExchange() {}

int     BitcoinExchange::size() const {return (_N);}

int     BitcoinExchange::binarySearch(std::vector<int>& arr, int target, int start, int end) {
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
    return low;
}

void    BitcoinExchange::addNumber(int i)
{
    //std::cout << _N << ":" << _v.size() << std::endl;
	if (_N == _v.size())
        throw BitcoinExchange::TooManyElements();
    _v.push_back(i);
	int     pos = binarySearch(_sorted, i, 0, _sorted.size() - 1);
    _sorted.insert(_sorted.begin() + pos, i);
}

int     BitcoinExchange::shortestBitcoinExchange() const
{
	if (_v.size() < 2)
        throw BitcoinExchange::TooFewElements();
    int _min = longestBitcoinExchange();
    for (size_t    i = 1; i < _sorted.size(); i++)
    {
        if (_sorted[i] - _sorted[i - 1] < _min)
            _min = _sorted[i] - _sorted[i - 1];
    }
    return (_min);
}

int     BitcoinExchange::longestBitcoinExchange() const
{
	if (_v.size() < 2)
        throw BitcoinExchange::TooFewElements();
    return (_sorted[_sorted.size() - 1] - _sorted[0]);
}

const char* BitcoinExchange::TooManyElements::what() const throw()
{ return ("Error: Too many elements."); }

const char* BitcoinExchange::TooFewElements::what() const throw()
{ return ("Error: Too few elements."); }

std::vector<int>*       BitcoinExchange::get_v() {return (&_v);}
unsigned int	        BitcoinExchange::get_N() {return (_N);}

std::ostream& operator<<( std::ostream& out, BitcoinExchange& a )
{
	std::vector<int>*	v = a.get_v();
	if (!a.size())
	{
		out << "[]";
		return (out);
	}
	out << "[";
	for (size_t i = 0;i < v->size() - 1;i++)
		out << (*v)[i] << ", ";
	out << (*v)[v->size() - 1] << "]";
	return (out);
}
