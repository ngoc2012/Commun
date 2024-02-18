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

#include <algorithm>

#include "Span.hpp"

Span::Span(unsigned int const & n): _N(n) {}

Span::Span(const Span& s)
{
    *this = s;
}

Span&	Span::operator=( const Span& s )
{
    for (unsigned int i = 0; i < s._N; i++)
        this->addNumber(s._v[i]);
    return (*this);
}

Span::~Span() {}

int     Span::size() const {return (_N);}

void    Span::addNumber(int i)
{
	if (_N == _v.size())
        throw Span::TooManyElements();
    _v.push_back(i);
    _sorted.push_back(i);
}

int     Span::shortestSpan()
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

int     Span::longestSpan()
{
    std::sort(_sorted.begin(), _sorted.end());
	if (_v.size() < 2)
        throw Span::TooFewElements();
    return (_sorted[_sorted.size() - 1] - _sorted[0]);
}

const char* Span::TooManyElements::what() const throw()
{ return ("Error: Too many elements."); }

const char* Span::TooFewElements::what() const throw()
{ return ("Error: Too few elements."); }

std::vector<int>*       Span::get_v() {return (&_v);}
unsigned int	        Span::get_N() {return (_N);}

std::ostream& operator<<( std::ostream& out, Span& a )
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
