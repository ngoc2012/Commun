/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/30 09:01:38 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotmyRequestForm.hpp"

//RobotmyRequestForm::RobotmyRequestForm(std::string t) : target(t)
RobotmyRequestForm::RobotmyRequestForm(std::string t)
{
	sign = false;
	target = t;
	sign_grade = 72;
	exec_grade = 45;
	std::cout << "RobotmyRequestForm " << name << " default constructor." << std::endl;
}

RobotmyRequestForm::RobotmyRequestForm(const RobotmyRequestForm& src): AForm(src)
{
	std::cout << "RobotmyRequestForm " << name << " copy constructor." << std::endl;
}

RobotmyRequestForm&	RobotmyRequestForm::operator=( RobotmyRequestForm const & src )
{
	AForm::operator=(src);
	return (*this);
}

RobotmyRequestForm::~RobotmyRequestForm() { std::cout << "RobotmyRequestForm " << name << " destructor." << std::endl; }

void	RobotmyRequestForm::beExecuted() const
{
	std::cout << "Vrmmmmm...vrmm..vrmm......." << std::endl;
	if(rand() % 2)
		std::cout << this->getTarget() << " was robotomized!" << std::endl;
	else
		std::cout << "The robotization messed up..." << std::endl;
}
