/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 08:54:04 by ngoc              #+#    #+#             */
/*   Updated: 2024/02/14 09:08:04 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

Span::Span(unsigned int n): _N(n) {}

Span::~Span() {}

int     Span::size() const {return (_N);}

void    Span::addNumber(int i) {}

std::ostream& operator<<( std::ostream& out, const Span& a )
{
	if (!a.size())
	{
		out << "[]";
		return (out);
	}
	out << "[";
	for (size_t i = 0;i < a.size() - 1;i++)
		out << a[i] << ", ";
	out << a[a.size() - 1] << "]";
	return (out);
}
