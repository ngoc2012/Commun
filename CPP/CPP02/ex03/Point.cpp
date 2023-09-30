/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khni <ael-khni@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 22:05:11 by ael-khni          #+#    #+#             */
/*   Updated: 2023/09/30 17:37:50 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

Point::Point( void ) : x(Fixed()), y(Fixed()) { }
Point::Point( const Fixed x, const Fixed y ) : x(x0), y(y0) {}
Point::Point( const Point &src ) : x(src.x), y(src.y) {}
Point::~Point() {}

Point&  Point::operator=( const Point &rhs ) {
	if (this == rhs)
		return (*this);
	x = rhs.getX();
	y = rhs.getY();
	return (*this);
}

Fixed Point::getX( void ) const {
    return this->_x;
}

Fixed Point::getY( void ) const {
    return this->_y;
}
