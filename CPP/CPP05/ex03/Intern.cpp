/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/01 19:09:49 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"

Intern::Intern() {std::cout << "Intern  default constructor." << std::endl;}

Intern::Intern(const Intern& src) {
	*this = src;
	std::cout << "Intern  copy constructor." << std::endl;
}

Intern&	Intern::operator=( Intern const & src )
{
	return (*this);
}

Intern::~Intern() { std::cout << "Intern  destructor." << std::endl; }

AForm	*Intern::makeForm(std::string f, std::string t)
{
	std::string fStr[] = {
	        "robotomy request",
	        "presidential pardon",
	        "shrubbery creation"
	};
	AForm*    fs[] = {
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
