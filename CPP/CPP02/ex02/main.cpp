/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 18:47:18 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/30 19:07:18 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

int main ( void ) {
    Fixed        a;
    Fixed const  b( Fixed( 5.05f ) * Fixed( 2 ) );
    Fixed const  c( Fixed(1000000000.05f ) * Fixed( 1000000000 ) );
    Fixed const  d( Fixed(1000000000.05f ) + Fixed( 1000000000 ) );
    Fixed const  e( Fixed(1000000000.05f ) - Fixed( 1000000000 ) );
    Fixed const  f( Fixed(1000000000.05f ) / Fixed( 1000000000 ) );
    Fixed const  g( Fixed( 5.05f ) - Fixed( 20 ) );

    std::cout << "a = " << a << std::endl;
    std::cout << "++a = " << ++a << std::endl;
    std::cout << "a = " << a << std::endl;
    std::cout << "a++ = " << a++ << std::endl;
    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "c = " << c << std::endl;
    std::cout << "d = " << d << std::endl;
    std::cout << "e = " << e << std::endl;
    std::cout << "f = " << f << std::endl;
    std::cout << "g = " << g << std::endl;

    std::cout << "max(a, b) = "  << Fixed::max( a, b ) << std::endl;

    return 0;
}
