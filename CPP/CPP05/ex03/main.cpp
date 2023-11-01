/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:17:48 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/01 14:43:47 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int	main()
{
	Bureaucrat	b2("b2", 2);
	std::cout << b2;
	Bureaucrat	b145("b145", 145);
	std::cout << b145;
	Bureaucrat	b70("b70", 70);
	std::cout << b70;
	Bureaucrat	b40("b40", 40);
	std::cout << b40;
	Bureaucrat	b10("b10", 10);
	std::cout << b10;

	Intern someRandomIntern;
	Form* rrf = someRandomIntern.makeForm("robotomy request1", "Bender");

	Form* s0 = someRandomIntern.makeForm("shrubbery creation", "Shru");
	if (s0)
	{
		try {
			std::cout << "s0.beSigned(b145);" << std::endl;
			s0.beSigned(b145);
		} catch (std::exception &e) {
			std::cout << e.what() << std::endl;
		}
		try {
			std::cout << "b70.signForm(s0);" << std::endl;
			b70.signForm(s0);
		} catch (std::exception &e) {
			std::cout << e.what() << std::endl;
		}
		try {
			std::cout << "s0.execute(b145);" << std::endl;
			s0.execute(b145);
		} catch (std::exception &e) {
			std::cout << e.what() << std::endl;
		}
		try {
			std::cout << "s0.execute(b70);" << std::endl;
			s0.execute(b70);
		} catch (std::exception &e) {
			std::cout << e.what() << std::endl;
		}
	}

	Form* r0 = someRandomIntern.makeForm("robotomy request", "Bender");
	if (r0)
	{
		RobotomyRequestForm r0("robot");
		try {
			std::cout << "r0.beSigned(b145);" << std::endl;
			r0.beSigned(b145);
		} catch (std::exception &e) {
			std::cout << e.what() << std::endl;
		}
		try {
			std::cout << "b70.signForm(r0);" << std::endl;
			b70.signForm(r0);
		} catch (std::exception &e) {
			std::cout << e.what() << std::endl;
		}
		try {
			std::cout << "r0.execute(b70);" << std::endl;
			r0.execute(b70);
		} catch (std::exception &e) {
			std::cout << e.what() << std::endl;
		}
		try {
			std::cout << "r0.execute(b40);" << std::endl;
			r0.execute(b40);
		} catch (std::exception &e) {
			std::cout << e.what() << std::endl;
		}
	}

	Form* p0 = someRandomIntern.makeForm("presidential pardon", "Macron");
	if (p0)
	{
		PresidentialPardonForm p0("PPF");
		try {
			std::cout << "p0.beSigned(b10);" << std::endl;
			p0.beSigned(b10);
		} catch (std::exception &e) {
			std::cout << e.what() << std::endl;
		}
		try {
			std::cout << "b2.signForm(p0);" << std::endl;
			b2.signForm(p0);
		} catch (std::exception &e) {
			std::cout << e.what() << std::endl;
		}
		try {
			std::cout << "p0.execute(b10);" << std::endl;
			p0.execute(b10);
		} catch (std::exception &e) {
			std::cout << e.what() << std::endl;
		}
		try {
			std::cout << "p0.execute(b2);" << std::endl;
			p0.execute(b2);
		} catch (std::exception &e) {
			std::cout << e.what() << std::endl;
		}
	}
	return (0);
}
