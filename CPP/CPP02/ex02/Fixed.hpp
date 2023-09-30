/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 21:20:40 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/30 15:50:28 by ngoc             ###   ########.fr       */
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
		int	max_overflow;
		int	min_overflow;
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

		bool    operator>( const Fixed &rhs ) const ;
		bool    operator<( const Fixed &rhs ) const ;
		bool    operator>=( const Fixed &rhs ) const ;
		bool    operator<=( const Fixed &rhs ) const ;
		bool    operator==( const Fixed &rhs ) const ;
		bool    operator!=( const Fixed &rhs ) const ;

		Fixed   operator+( const Fixed &rhs ) const ;
		Fixed   operator-( const Fixed &rhs ) const ;
		Fixed   operator*( const Fixed &rhs ) const ;
		Fixed   operator/( const Fixed &rhs ) const ;

		Fixed&  operator++( void ); // prefix
		Fixed   operator++( int ); // postfix
		Fixed&  operator--( void ); // prefix
		Fixed   operator--( int ); // postfix

		static Fixed& min( Fixed &a, Fixed &b );
		static const Fixed& min( const Fixed &a, const Fixed &b );
		static Fixed& max( Fixed &a, Fixed &b );
		static const Fixed& max( const Fixed &a, const Fixed &b );
		/*
		   Static Function Members
		   By declaring a function member as static, you make it independent of any
		   particular object of the class. A static member function can be called
		   even if no objects of the class exist and the static functions are accessed
		   using only the class name and the scope resolution operator ::.

		   A static member function can only access static data member, other static
		   member functions and any other functions from outside the class.

		   Static member functions have a class scope and they do not have access
		   to the this pointer of the class. You could use a static member function
		   to determine whether some objects of the class have been created or not.
		 */

		bool	getOverFlow( void ) const;
		void	setOverFlow( bool );

		int	getMaxOverFlow( void ) const;
		void	setMaxOverFlow( int );

		int	getMinOverFlow( void ) const;
		void	setMinOverFlow( int );

		void	init( void );
};

std::ostream&	operator<<( std::ostream& o, const Fixed& n );

#endif
