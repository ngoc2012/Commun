/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:17:48 by ngoc              #+#    #+#             */
/*   Updated: 2024/02/13 17:36:27 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
#include <iostream>

#include "Array.hpp"

Array::Array() {
	srand((unsigned) time(NULL));
}

Array::Array(const Array& src) { *this = src; }

Array&	Array::operator=( Array const & src )
{
	(void) src;
	return (*this);
}

Array::~Array() {}

Array*	Array::generate(void)
{
	std::srand(static_cast<unsigned int>(std::time(0)));
	

	if (std::rand() % 4 == 1)
		return (new A);
	else if (std::rand() % 4 == 2)
		return (new B);
	else if (std::rand() % 4 == 3)
		return (new C);
	return (0);
}

void	Array::identify(Array* b)
{
	if (dynamic_cast<A*>(b))
		std::cout << "A";
	else if (dynamic_cast<B*>(b))
		std::cout << "B";
	else if (dynamic_cast<C*>(b))
		std::cout << "C";
	else
		std::cout << "unknown";
}

void	Array::identify(Array& b)
{
	bool	err = true;
	try
	{
		A& a = dynamic_cast<A&>(b);
		std::cout << "A";
		err = false;
		(void) a;
	}
	catch(const std::exception& e) {}
	try
	{
		B& a = dynamic_cast<B&>(b);
		std::cout << "B";
		err = false;
		(void) a;
	}
	catch(const std::exception& e) {}
	try
	{
		C& a = dynamic_cast<C&>(b);
		std::cout << "C";
		err = false;
		(void) a;
	}
	catch(const std::exception& e) {}
	if (err)
		std::cout << "unknown";
}
