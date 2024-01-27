/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2024/01/27 14:48:26 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm(std::string t)
{
	_sign = false;
	_target = t;
	_sign_grade = 72;
	_exec_grade = 45;
	std::cout << "RobotomyRequestForm " << _name << " default constructor." << std::endl;
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& src): AForm(src)
{
	std::cout << "RobotomyRequestForm " << _name << " copy constructor." << std::endl;
}

RobotomyRequestForm&	RobotomyRequestForm::operator=( RobotomyRequestForm const & src )
{
	AForm::operator=(src);
	return (*this);
}

RobotomyRequestForm::~RobotomyRequestForm() { std::cout << "RobotomyRequestForm " << _name << " destructor." << std::endl; }

void	RobotomyRequestForm::beExecuted() const
{
	srand((unsigned) time(NULL));
	std::cout << "Vrmmmmm...vrmm..vrmm......." << std::endl;
	if(rand() % 2)
		std::cout << target << " was robotomized!" << std::endl;
	else
		std::cout << "The robotization messed up..." << std::endl;
}
