/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/01 14:33:38 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"

Intern::Intern() {std::cout << "Intern " << name << " default constructor." << std::endl;}

Intern::Intern(const Intern& src) {
	*this = src;
	std::cout << "Intern " << name << " copy constructor." << std::endl;
}

Intern&	Intern::operator=( Intern const & src )
{
	return (*this);
}

Intern::~Intern() { std::cout << "Intern " << name << " destructor." << std::endl; }

void		Intern::beSigned( Bureaucrat& b)
{
	if (sign)
	{
		std::cout << "Intern " << name << " already signed." << std::endl;
		return ;
	}
	if (b.getGrade() > sign_grade)
	{
		std::cerr << "Intern " << name << " could not be signed by " << b.getName() << " because: ";
		throw Intern::GradeTooLowException();
	}
	sign = true;
	std::cout << "Intern " << name << " signed by " << b.getName() <<  "." << std::endl;
}
