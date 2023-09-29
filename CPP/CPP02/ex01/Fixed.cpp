/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 08:44:11 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/29 13:53:26 by ngoc             ###   ########.fr       */
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
   
   number = (sign ? -1:1) * 2^(exponent) * 1.(mantissa bits)

s: 0 is used to represent a positive number, and 1 is used to represent a negative number

Exponent
* in the number 3.14 x 10^5, the exponent is 5.
* a bias 127 is applied to the exponent to allow for positive and negative exponents -> the lowest possible exponent is actually -126

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

/*
Exponent (8 bits):

    Normalize the number: 2025.2025 becomes 2.0252025 by moving the decimal point to the left.

    Count the number of positions you moved the decimal point. In this case, you moved it three positions to the left.

    Add the IEEE 754 bias to the exponent. The bias for 32-bit IEEE 754 representation is 127.

    Convert the biased exponent to binary:
        Decimal biased exponent: 3 (from step 2)
        Bias: 127
        Biased exponent = 3 + 127 = 130 (in decimal)
        In binary, 130 is 10000010.

Mantissa (23 bits):

    Convert the fractional part (0.0252025) to binary. To do this, multiply the fractional part by 2 repeatedly while keeping track of the whole number part:
        0.0252025 * 2 = 0.050405 (First binary digit is 0)
        0.050405 * 2 = 0.10081 (Next binary digit is 0)
        0.10081 * 2 = 0.20162 (Next binary digit is 0)
        0.20162 * 2 = 0.40324 (Next binary digit is 0)
        0.40324 * 2 = 0.80648 (Next binary digit is 0)
        0.80648 * 2 = 1.61296 (Next binary digit is 1)
        0.61296 * 2 = 1.22592 (Next binary digit is 1)
        0.22592 * 2 = 0.45184 (Next binary digit is 0)
        0.45184 * 2 = 0.90368 (Next binary digit is 0)
        0.90368 * 2 = 1.80736 (Next binary digit is 1)
        0.80736 * 2 = 1.61472 (Next binary digit is 1)
        0.61472 * 2 = 1.22944 (Next binary digit is 1)

    Continue this process until you have obtained 23 bits of the mantissa.

The resulting binary representation of the mantissa is 00110010011101111011001.
Final:

   01000001 00011001 00111011 11011001

   01000100 11111101 00100110 01111011

So, in a 32-bit IEEE 754 binary floating-point representation:

    Sign Bit: 0 (positive)
    Exponent: 10000010 (biased exponent)
    Mantissa: 00110010011101111011001

   seeeeeee emmmmmmm mmmmmmmm mmmmmmmm    meaning
  31                              0    bit #
  s = sign bit, e = exponent, m = mantissa

   01000100 11111101 00100110 01111011
*/
#include <cmath>
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
