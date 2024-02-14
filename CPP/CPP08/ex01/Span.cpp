/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 08:54:04 by ngoc              #+#    #+#             */
/*   Updated: 2024/02/14 10:24:32 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

Span::Span(unsigned int n): _N(n) {}

Span::~Span() {}

int     Span::size() const {return (_N);}

int     Span::binarySearch(std::vector<int>& arr, int target, int start, int end) {
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

void    Span::addNumber(int i)
{
	if (_N == _v.size())
        throw Span::TooFewElements();
    _v.push_back(i);
	int     pos = binarySearch(_sorted, i, 0, _sorted.size());
    _sorted.insert(_sorted.begin() + pos, i);
}

int     Span::shortestSpan() const
{
	if (_v.size() < 2)
        throw Span::TooFewElements();
    int _min = longestSpan();
    for (size_t    i = 1; i < _sorted.size(); i++)
    {
        if (_sorted[i] - _sorted[i - 1] < _min)
            _min = _sorted[i] - _sorted[i - 1];
    }
    return (_min);
}

int     Span::longestSpan() const
{
	if (_v.size() < 2)
        throw Span::TooFewElements();
    return (_sorted[_sorted.size() - 1] - _sorted[0]);
}

const char* Span::TooManyElements::what() const throw()
{ return ("Error: Too many elements."); }

const char* Span::TooFewElements::what() const throw()
{ return ("Error: Too few elements."); }

std::vector<int>*    Span::get_v() {return (&_v);}

std::ostream& operator<<( std::ostream& out, const Span& a )
{
	std::vector<int>*	v = a.get_v();
	if (!a.size())
	{
		out << "[]";
		return (out);
	}
	out << "[";
	for (int i = 0;i < a.size() - 1;i++)
		out << a[i] << ", ";
	out << a[a.size() - 1] << "]";
	return (out);
}
