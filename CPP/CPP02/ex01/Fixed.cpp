/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 08:44:11 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/29 09:54:17 by ngoc             ###   ########.fr       */
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

Fixed::Fixed( const int n ) : fp( n << fb ) {
    std::cout << "Int constructor called" << std::endl;
}

Fixed::Fixed( const float n ) : fp( std::roundf( n * ( 1 << fb ) ) ) {
    std::cout << "Float constructor called" << std::endl;
}

int	Fixed::getRawBits( void ) const
{
	std::cout << "getRawBits member function called" << std::endl;
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
