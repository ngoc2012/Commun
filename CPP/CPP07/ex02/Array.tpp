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

Array::Array() {
	_a = new T();
	_size = 0;
}

Array::Array(const Array& src) { *this = src; }

Array&	Array::operator=( Array const & src )
{
	(void) src;
	return (*this);
}

Array::~Array() {}

Array( void ) : _arr( new T() ), _size( 0 ) {};
    Array( unsigned int n ) : _arr( new T[n] ), _size( n ) {};
    Array( const Array& rhs ) : _arr( new T[rhs.size()] ), _size( rhs.size() ) {
        for ( unsigned int i( 0 ); i < _size; i++ )
            _arr[i] = rhs._arr[i];
    };