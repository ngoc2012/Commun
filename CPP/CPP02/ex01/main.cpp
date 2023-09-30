/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 18:45:45 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/30 15:16:30 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include <limits>

int main(void) {

	Fixed       a;
	//Fixed const b( 10 );
	//Fixed const c( 42.42f );
	//Fixed const d( b );
	//Fixed       a1;
	//Fixed       a2;
	//Fixed       a3;
	//Fixed       a4;

	//a = Fixed(10000000000000.0f);
	//a = Fixed( -1000000000 );
	//a = Fixed( -42.42f );
	//a = Fixed( -1234.4321f );
	a = Fixed( -8388608 );
	std::cout << "a is " << a << std::endl;
/*
	a = Fixed( -1234.4321f );
	a1 = Fixed( 2147483647 );
	a2 = Fixed( -2147483647 );
	//a3 = Fixed(std::numeric_limits<float>::max());
	//a4 = Fixed(std::numeric_limits<float>::min());
	//a3 = Fixed(3.402823465e+38f);
	//a4 = Fixed(1.175494352e-38f);
	a3 = Fixed(10000000000000.0f);
	a4 = Fixed(-10000000000000.0f);
	//a = Fixed( 42.42f );
	//a = Fixed( 12345678.87654321f );
	std::cout << "a is " << a << std::endl;
	std::cout << "a1 is " << a1 << std::endl;
	std::cout << "a2 is " << a2 << std::endl;
	//std::cout << 3.402823466e+38f << std::endl;
	//std::cout << 1.175494351e-38f << std::endl;
	std::cout << "a3 is " << a3 << std::endl;
	std::cout << "a4 is " << a4 << std::endl;
	std::cout << "b is " << b << std::endl;
	std::cout << "c is " << c << std::endl;
	std::cout << "d is " << d << std::endl;

	std::cout << "====================================================\n";

	std::cout << "a is " << a.toInt() << " as integer" << std::endl;
	std::cout << "a1 is " << a1.toInt() << " as integer" << std::endl;
	std::cout << "a2 is " << a2.toInt() << " as integer" << std::endl;
	std::cout << "a3 is " << a3.toInt() << " as integer" << std::endl;
	std::cout << "a4 is " << a4.toInt() << " as integer" << std::endl;
	std::cout << "b is " << b.toInt() << " as integer" << std::endl;
	std::cout << "c is " << c.toInt() << " as integer" << std::endl;
	std::cout << "d is " << d.toInt() << " as integer" << std::endl;
*/	
	return 0;
}
