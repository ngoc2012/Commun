/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2024/01/27 18:36:15 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm(const std::string t): AForm("RobotomyRequestForm", 72, 45), _target(t) {}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& src): AForm(src) { }

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
