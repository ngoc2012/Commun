/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:17:48 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/21 21:22:39 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"

Base::Base() {
	srand((unsigned) time(NULL));
}

Base::Base(const Base& src) { *this = src; }

Base&	Base::operator=( Base const & src )
{
	(void) src;
	return (*this);
}

Base::~Base() {}

Base*	Base::generate(void)
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

void	Base::identify(Base* b)
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

void	Base::identify(Base& b)
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
