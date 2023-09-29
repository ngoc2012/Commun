/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 18:45:45 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/29 20:56:17 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

int main(void) {

	Fixed       a;
	Fixed const b( 10 );
	Fixed const c( 42.42f );
	Fixed const d( b );
	Fixed       a1;
	Fixed       a2;

	a = Fixed( 1234.4321f );
	a1 = Fixed( 2147483647 );
	a2 = Fixed( -2147483647 );
	//a = Fixed( 42.42f );
	//a = Fixed( 12345678.87654321f );
	std::cout << "a is " << a << std::endl;
	std::cout << "a1 is " << a1 << std::endl;
	std::cout << "a2 is " << a2 << std::endl;
	std::cout << "b is " << b << std::endl;
	std::cout << "c is " << c << std::endl;
	std::cout << "d is " << d << std::endl;

	std::cout << "a is " << a.toInt() << " as integer" << std::endl;
	std::cout << "a1 is " << a1.toInt() << " as integer" << std::endl;
	std::cout << "a2 is " << a2.toInt() << " as integer" << std::endl;
	std::cout << "b is " << b.toInt() << " as integer" << std::endl;
	std::cout << "c is " << c.toInt() << " as integer" << std::endl;
	std::cout << "d is " << d.toInt() << " as integer" << std::endl;

	return 0;
}
