/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:17:48 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/30 10:44:28 by ngoc             ###   ########.fr       */
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
	ShrubberyCreationForm s0("home");
	try {
		s0.beSigned(b145);
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	try {
		b145.signForm(s0);
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	try {
		s0.execute(b145);
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	try {
		s0.execute(b2);
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	RobotomyRequestForm r0("robot");
	try {
		s0.beSigned(b145);
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	try {
		b145.signForm(r0);
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	try {
		r0.execute(b145);
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	try {
		r0.execute(b2);
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	PresidentialPardonForm p0("PPF");
	try {
		p0.beSigned(b145);
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	try {
		b145.signForm(p0);
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	try {
		p0.execute(b145);
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	try {
		p0.execute(b2);
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	return (0);
}
