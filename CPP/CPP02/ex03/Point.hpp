/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 18:13:09 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/30 18:28:09 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_HPP
# define POINT_HPP

#include "Fixed.hpp"

class	Point
{
	private:
		const Fixed x;
		const Fixed y;
	public:
		Point();
		Point( const float x, const float y );
		Point( const Point& );
		~Point();

		Point&  operator=( const Point& );
		Fixed getX( void ) const ;
		Fixed getY( void ) const ;

};

bool	bsp( Point const a, Point const b, Point const c, Point const point );


#endif // POINT_HPP
