/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:17:48 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/21 19:17:59 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

Base::Base() {}

Base::Base(const Base& src) { *this = src; }

Base&	Base::operator=( Base const & src )
{
	(void) src;
	return (*this);
}

Base::~Base() {}

Base*	Base::generate(void)
{
	// Seed the random number generator with the current time
	std::srand(static_cast<unsigned int>(std::time(0)));

	if (std::rand() % 3 == 1)
		return (new A);
	else if (std::rand() % 3 == 2)
		return (new B);
	else
		return (new C);
}

void	Base::identify(Base* b)
{
	if (dynamic_cast<A*>(b))
		std::cout << "A" << std::endl;
	else if (dynamic_cast<B*>(b))
		std::cout << "B" << std::endl;
	else if (dynamic_cast<C*>(b))
		std::cout << "C" << std::endl;
	else
		std::cout << "unknown" << std::endl;
}

void	Base::identify(Base& b)
{
	try
	{
	} catch(const std::exception& e) {}
}
