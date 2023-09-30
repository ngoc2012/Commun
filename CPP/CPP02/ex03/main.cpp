/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 18:48:48 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/30 18:59:40 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

/*
Input: A = (0, 0), B = (10, 30), C = (20, 0), P(10, 15)
Output: Inside
Explanation:
              B(10,30)
                / \
               /   \
              /     \
             /   P   \      P'
            /         \
     A(0,0) ----------- C(20,0) 

Input: A = (0, 0), B = (10, 30), C = (20, 0), P(30, 15)
Output: Outside
Explanation:
              B(10,30)
                / \
               /   \
              /     \
             /       \      P
            /         \
     A(0,0) ----------- C(20,0) 
*/

int	main ( void ) {
	if ( bsp( Point(0, 0), Point(1, 0), Point(0, 0), Point(0, 1) ) == true ) {
		std::cout << "Point is in the triangle" << std::endl;
	} else {
		std::cout << "Point is not in the triangle" << std::endl;
	}
	if ( bsp( Point(0, 0), Point(0, 0), Point(0, 0), Point(0, 1) ) == true ) {
		std::cout << "Point is in the triangle" << std::endl;
	} else {
		std::cout << "Point is not in the triangle" << std::endl;
	}
	if ( bsp( Point(0, 0), Point(10, 30), Point(20, 0), Point(10, 15) ) == true ) {
		std::cout << "Point is in the triangle" << std::endl;
	} else {
		std::cout << "Point is not in the triangle" << std::endl;
	}
	if ( bsp( Point(0, 0), Point(10, 30), Point(20, 0), Point(30, 15) ) == true ) {
		std::cout << "Point is in the triangle" << std::endl;
	} else {
		std::cout << "Point is not in the triangle" << std::endl;
	}
	return (0);
}
