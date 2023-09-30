/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 18:48:21 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/30 19:06:19 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

static Fixed	area2( Point const p1, Point const p2, Point const p3 ) {
	Fixed	r;
	r = r + p1.getX() * p2.getY() + p2.getX() * p3.getY() + p3.getX() * p1.getY();
	r = r - p2.getX() * p1.getY() - p3.getX() * p2.getY() - p1.getX() * p3.getY();
	if (r < 0)
		r = Fixed() - r;
	return (r);
}

bool	bsp( Point const a, Point const b, Point const c, Point const p) {
	Fixed r1 = area2( a, b, c );
	Fixed r2 = area2( p, a, b );
	Fixed r3 = area2( p, a, c );
	Fixed r4 = area2( p, c, b );
	if (r1 == Fixed())
	{
		std::cerr << "Error: triangle not valid\n";
		return (false);
	}
	return  (r1  ==  r2 + r3 + r4);
}
