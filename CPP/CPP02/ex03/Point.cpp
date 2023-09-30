/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 18:48:32 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/30 18:48:34 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

Point::Point( void ) : x(Fixed()), y(Fixed()) { }
Point::Point( const float x0, const float y0 ) : x(Fixed(x0)), y(Fixed(y0)) {}
Point::Point( const Point &src ) : x(src.x), y(src.y) {}
Point::~Point() {}

Point&	Point::operator=( const Point &src ) {
	(void) src;
	return (*this);
}

Fixed	Point::getX( void ) const { return (x); }
Fixed	Point::getY( void ) const { return (y); }
