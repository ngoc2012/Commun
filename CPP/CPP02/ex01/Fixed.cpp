/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 08:44:11 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/30 15:03:37 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

Fixed::Fixed()
{
    std::cout << "Default constructor called" << std::endl;
    fp = 0;
    overflow = false;
}

Fixed::~Fixed()
{
    std::cout << "Destructor called" << std::endl;
}

static void	assignment(Fixed &des, const Fixed &src)
{
	std::cout << "Copy assignment operator called" << std::endl;
	des.setRawBits(src.getRawBits());
	des.setOverFlow(src.getOverFlow());
}

Fixed&	Fixed::operator=( const Fixed &src )
{
	assignment(*this, src);
	return (*this);
}

Fixed::Fixed( const Fixed &src )
{
	std::cout << "Copy constructor called" << std::endl;
	assignment(*this, src);
}

/*
1234.4321	10011010 010.01101 11010011110001
316015		10011010 010 01101 111
316014		10011010 010 01101 110

42.42		101010.01 101011 10000101001
10859.5		101010 01 101011.1
10859.52	101010 01 101011.100001010001111011
10859		101010 01 101011
10860		101010 01 101100

10859.4		101010 01 101011.0110011001100110011
10859.49	101010 01 101011.0111110101110000101

2147483647	01111111111111111111111111111111
4294967040	11111111111111111111111100000000
2147483392	01111111111111111111111100000000

8388607		01111111 11111111 11111111
-8388607	11111111 11111111 11111111

*/

// Function to print the binary representation of an integer
void	printBinaryInt(int n) {
	int	numBits = sizeof(int) * 8;
	for (int i = numBits - 1; i >= 0; i--) {
		int	bit = (n >> i) & 1;
		std::cout << bit;
	}
	std::cout << std::endl;
}

//#include <cstdint>
// Function to print the binary representation of a float
void	printBinaryFloat(float f) {
	unsigned int*	floatAsInt = reinterpret_cast<unsigned int*>(&f);
	for (int i = 31; i >= 0; i--) {
		unsigned int	bit = (*floatAsInt >> i) & 1;
		std::cout << bit;
	}
	std::cout << std::endl;
}

bool	checkOverflowInt(const int n, int fb)
{
	int	max = 1;
	for (int i = 0; i < fb - 2; i++)
		max = (max << 1) & 1;
	if (n > max || n < -max)
		return (true);
	return (false);
	/*
	std::cout << "here " << n << std::endl;
	printBinaryInt(n);
	for (int i = len - 2; i > len - fb - 1; i--)
	{
		std::cout << i << " - ";
		printBinaryInt(n >> i);
		if ((n >> i) & 1)
			return (true);
	}
	return (false);
	*/
}

Fixed::Fixed( const int n )
{
	//printBinaryInt(n);
	if (n < 0)
		overflow = checkOverflowInt(-n, fb);
	else
		overflow = checkOverflowInt(n, fb);
	fp = n << fb;
	//printBinaryInt(fp);
	int	bit_1 = 1 << (sizeof(int) * 8 - 1);
	//printBinaryInt(bit_1);
	if (n > 0)
		fp = fp & ~bit_1;
	else
		fp = fp | bit_1;
	//printBinaryInt(fp);
	std::cout << "Int constructor called" << std::endl;
}

Fixed::Fixed( const float n )
{
	std::cout << static_cast<int>(n) << std::endl;
	if (n < 0)
		overflow = checkOverflowInt(static_cast<int>(-n), fb);
	else
		overflow = checkOverflowInt(static_cast<int>(n), fb);
	//printBinaryFloat(n);
	if (static_cast<int>(n * (1 << (fb + 1))) & 1)
		fp = static_cast<float>(static_cast<int>( n * ( 1 << fb ) + 1 ) );
	else
		fp = static_cast<float>(static_cast<int>( n * ( 1 << fb ) ) );
	//printBinaryInt(fp);
	int	bit_1 = 1 << (sizeof(int) * 8 - 1);
	//printBinaryInt(bit_1);
	if (n > 0)
		fp = fp & ~bit_1;
	else
		fp = fp | bit_1;
	//printBinaryInt(fp);
	std::cout << "Float constructor called" << std::endl;
}

int	Fixed::getRawBits( void ) const
{
	return (fp);
}

void	Fixed::setRawBits( int const raw ) {
	fp = raw;
}

float	Fixed::toFloat( void ) const
{
	if (getOverFlow())
		return (0);
	return static_cast<float>( getRawBits() ) / ( 1 << fb );
}

int	Fixed::toInt( void ) const
{
	if (getOverFlow())
		return (0);
	return fp >> fb;
}

bool	Fixed::getOverFlow( void ) const { return (overflow); }
void	Fixed::setOverFlow( bool o ) { overflow = o; }

std::ostream	&operator<<( std::ostream &o, const Fixed &n )
{
	if (n.getOverFlow())
		o << "NaN";
	else
		o << n.toFloat();
	return o;
}
/*
https://www.youtube.com/watch?v=gc1Nl3mmCuY

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
1 -> 1 * 2^8
42: 00000000 00000000 00000000 00101010
->  00000000 00000000 00101010 00000000
42 -> 42 * 2^8

*/


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



To avoid the decimal separator, multiply the decimal number with the base raised to the power of decimals in result:
42.42×28 = 10860

Divide by the base 2 to get the digits from the remainders:
 		Quotient	Remainder 	Bit #
(10860)/2	5430		0		0
(5430)/2	2715		0		1
(2715)/2	1357		1		2
(1357)/2	678		1		3
(678)/2		339		0		4
(339)/2		169		1		5
(169)/2		84		1		6
(84)/2		42		0		7
(42)/2		21		0		8
(21)/2		10		1		9
(10)/2		5		0		10
(5)/2		2		1		11
(2)/2		1		0		12
(1)/2		0		1		13

= (10101001101011) / 2^8

= (101010.01101011)


42.42:   101010.0110101110000101001
*/

