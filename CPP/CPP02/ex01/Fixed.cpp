/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 08:44:11 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/29 11:21:52 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

Fixed::Fixed()
{
    std::cout << "Default constructor called" << std::endl;
    fp = 0;
}

Fixed::~Fixed()
{
    std::cout << "Destructor called" << std::endl;
}

static void	assignment(Fixed &des, Fixed &src)
{
	std::cout << "Copy assignment operator called" << std::endl;
	des.setRawBits(src.getRawBits());
}

Fixed&	Fixed::operator=( Fixed &src )
{
	assignment(*this, src);
	return (*this);
}

Fixed::Fixed( Fixed &src )
{
	std::cout << "Copy constructor called" << std::endl;
	assignment(*this, src);
}

/*
    seeeeeee emmmmmmm mmmmmmmm mmmmmmmm    meaning
   31                              0    bit #
   s = sign bit, e = exponent, m = mantissa

s: 0 is used to represent a positive number, and 1 is used to represent a negative number
e: in the number 3.14 x 10^5, the exponent is 5.
m: represents the fractional part of a number in binary form

The mantissa is typically normalized, which means it is adjusted to start with a 1 (binary point)

Example:
fb = 8
1 : 00000000 00000000 00000000 00000001
->  00000000 00000000 00000001 00000000

*/
Fixed::Fixed( const int n ) : fp( n << fb ) {
    std::cout << "Int constructor called" << std::endl;
}

Fixed::Fixed( const float n ) : fp( std::roundf( n * ( 1 << fb ) ) ) {
    std::cout << "Float constructor called" << std::endl;
}

int	Fixed::getRawBits( void ) const
{
	return (fp);
}

void	Fixed::setRawBits( int const raw ) {
	fp = raw;
}

float	Fixed::toFloat( void ) const {
    return static_cast<float>( getRawBits() ) / ( 1 << fb );
}

int	Fixed::toInt( void ) const
{
    return fp >> fb;
}

std::ostream&	operator<<( std::ostream & o, Fixed const & i )
{
    o << i.toFloat();
    return o;
}
