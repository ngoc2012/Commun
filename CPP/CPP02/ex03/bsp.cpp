/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khni <ael-khni@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 22:13:17 by ael-khni          #+#    #+#             */
/*   Updated: 2023/09/30 17:56:52 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

static Fixed   area( Point const p1, Point const p2, Point const p3 ) {
	Fixed	r;
	r += p1.getX() * p2.getY() + p2.getX() * p3.getY() + p3.getX() * p1.getY();
	r -= p2.getX() * p1.getY() + p3.getX() * p2.getY() + p1.getX() * p3.getY();
	if (r < 0)
		r = -r;
	return (r / 2);
}

bool bsp( Point const a, Point const b, Point const c, Point const point) {
	Fixed	abcArea = abs(area( a, b, c ));
	Fixed	pabArea = abs(area( point, a, b ));
	Fixed	pbcArea = abs(area( point, b, c ));
	Fixed	pcaArea = abs(area( point, c, a ));

	return  ( area( a, b, c ) == pabArea + pbcArea + pcaArea );
}
