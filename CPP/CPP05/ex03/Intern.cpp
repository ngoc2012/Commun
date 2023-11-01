/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/01 21:27:54 by ngoc             ###   ########.fr       */
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
	(void) src;
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
	        new RobotomyRequestForm( t ),
	        new PresidentialPardonForm( t ),
	        new ShrubberyCreationForm( t )
	};
	for (int i = 0; i < N_FORMS; i++)
		if (f == fStr[i])
		{
			int	i0 = i + 1;
			while (i0 < N_FORMS)
				delete(fs[i0++]);
			return (fs[i]);
		}
		else
			delete(fs[i]);
	std::cerr << "Form: " << f << " not found" << std::endl;
	return 0;
}
