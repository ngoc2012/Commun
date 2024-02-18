/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 06:21:20 by ngoc              #+#    #+#             */
/*   Updated: 2024/01/29 06:21:33 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include "whatever.hpp"

int main( void )
{
    int a = 2;
    int b = 3;

    swap( a, b );
    std::cout << "a = " << a << ", b = " << b << std::endl;

    std::cout << "min( a, b ) = " << min( a, b ) << std::endl;
    std::cout << "max( a, b ) = " << max( a, b ) << std::endl;

    std::string c = "string1";
    std::string d = "string2";

    swap(c, d);
    std::cout << "c = " << c << ", d = " << d << std::endl;

    std::cout << "min( c, d ) = " << min( c, d ) << std::endl;
    std::cout << "max( c, d ) = " << max( c, d ) << std::endl;
    
    double e = -0.2;
    double f = 3.5;

    swap( a, b );
    std::cout << "e = " << e << ", f = " << f << std::endl;

    std::cout << "min( e, f ) = " << min( e, f ) << std::endl;
    std::cout << "max( e, f ) = " << max( e, f ) << std::endl;

    return 0;
}
