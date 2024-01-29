/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:17:48 by ngoc              #+#    #+#             */
/*   Updated: 2024/01/29 13:18:24 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
#include <iostream>

#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {
	srand((unsigned) time(NULL));
}

PmergeMe::PmergeMe(const PmergeMe& src) { *this = src; }

PmergeMe&	PmergeMe::operator=( PmergeMe const & src )
{
	(void) src;
	return (*this);
}

PmergeMe::~PmergeMe() {}

PmergeMe*	PmergeMe::generate(void)
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

void	PmergeMe::identify(PmergeMe* b)
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

void	PmergeMe::identify(PmergeMe& b)
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
