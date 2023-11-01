/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/01 14:39:06 by ngoc             ###   ########.fr       */
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

AForm	*Intern::makeForm(std::string f, std::string t)
{
	std::string fStr[] = {
	        "robotomy request",
	        "presidential pardon",
	        "shrubbery creation"
	};
	Form*    fs[] = {
	        new RobotomyRequestForm( target ),
	        new PresidentialPardonForm( target ),
	        new ShrubberyCreationForm( target )
	};
	for (int i = 0; i < N_FORMS; i++)
		if (f == fStr[i])
			return (fs[i]);
	std::cerr << "Form: " << f << " not found" << std::endl;
	return 0;
}
