/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 08:54:04 by ngoc              #+#    #+#             */
/*   Updated: 2024/02/14 09:57:51 by ngoc             ###   ########.fr       */
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
        throw std::exception();
    _v.push_back();
	int insertPos = binarySearch(_sorted, i, 0, _v.size());
    arr.insert(arr.begin() + insertPos, num);
}

int     Span::shortestSpan() const
{
}

int     Span::longestSpan() const;
{
}

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
