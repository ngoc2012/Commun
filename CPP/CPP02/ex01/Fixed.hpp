/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 21:20:40 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/30 09:14:52 by ngoc             ###   ########.fr       */
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
		bool	overflow;
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

		bool	getOverFlow( void ) const;
		void	setOverFlow( void );
};

std::ostream&	operator<<( std::ostream& o, const Fixed& n );

#endif
