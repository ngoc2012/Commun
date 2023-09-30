/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khni <ael-khni@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 22:03:31 by ael-khni          #+#    #+#             */
/*   Updated: 2023/09/30 17:20:20 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_HPP
# define POINT_HPP

#include "Fixed.hpp"

class Point
{
	private:
		const Fixed x;
		const Fixed y;

	public:
		Point();
		Point( const float x, const float y );
		Point( const Point &src );
		~Point();

		Point&  operator=( const Point &rhs );

		Fixed getX( void ) const ;
		Fixed getY( void ) const ;

};

bool bsp( Point const a, Point const b, Point const c, Point const point );


#endif // POINT_HPP
