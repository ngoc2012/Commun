/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 21:20:40 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/29 14:31:39 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

#include <iostream>

class Fixed
{
	private:
		int	fp;
		static const int	fb = 8;
	public:
		Fixed( void );
		Fixed( const Fixed& );
		Fixed&	operator=( const Fixed& );
		~Fixed( void );
		Fixed( const int n );
		Fixed( const float n );

		int     getRawBits( void ) const;
		void    setRawBits( int const raw );

		float   toFloat( void ) const;
		int     toInt( void ) const;
};

std::ostream&	operator<<( std::ostream& o, Fixed& n );

#endif
