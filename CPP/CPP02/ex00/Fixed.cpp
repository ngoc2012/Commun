/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 08:44:11 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/29 09:08:39 by ngoc             ###   ########.fr       */
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
	if (&des != &src)
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

int	Fixed::getRawBits( void ) const
{
    std::cout << "getRawBits member function called" << std::endl;
    return (fp);
}

void	Fixed::setRawBits( int const raw ) {
    fp = raw;
}
