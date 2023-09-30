/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khni <ael-khni@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 22:13:17 by ael-khni          #+#    #+#             */
/*   Updated: 2023/09/30 18:21:45 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

static Fixed	area2( Point const p1, Point const p2, Point const p3 ) {
	Fixed	r;
	r = r + p1.getX() * p2.getY() + p2.getX() * p3.getY() + p3.getX() * p1.getY();
	r = r - p2.getX() * p1.getY() - p3.getX() * p2.getY() - p1.getX() * p3.getY();
	if (r < 0)
		r = Fixed() - r;
	std::cout << r << std::endl;
	return (r);
}

bool	bsp( Point const a, Point const b, Point const c, Point const p) {
	return  ( area2( a, b, c ) == area2( p, a, b ) + area2( p, b, c ) + area2( p, c, a ) );
}
