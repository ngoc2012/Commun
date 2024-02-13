/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:17:48 by ngoc              #+#    #+#             */
/*   Updated: 2024/02/13 17:36:27 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Array.hpp"

Array::Array() {
	_a = new T();
	_size = 0;
}

Array::Array(size_t n) {
	_a = new T[n];
	_size = n;
}

Array::Array(const Array& src)
{
	*this = src;
}

Array&	Array::operator=( Array const & src )
{
	for ( size_t i = 0; i < src.size(); i++ )
        _arr[i] = src[i];
	return (*this);
}

template <typename T>
Array::~Array() { delete [] _a; }

template <typename T>
T& Array::operator[](size_t i) const {
    if (i >= _size)
        throw IndexError();
    return _a[i];
}

template <typename T>
std::ostream& operator<<( std::ostream& out, const Array<T>& a )
{
    for (size_t i = 0;i < a.size();i++)
        out << a[i] << ", ";
    return out;
}
