/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/30 08:59:29 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotmyRequestForm.hpp"

//RobotmyRequestForm::RobotmyRequestForm(std::string t) : target(t)
RobotmyRequestForm::RobotmyRequestForm(std::string t)
{
	sign = false;
	target = t;
	sign_grade = 145;
	exec_grade = 137;
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
	std::ofstream file;

	file.open(std::string(target + "_shrubbery").c_str(),
		std::ios::out | std::ios::trunc);
	// https://ascii.co.uk/art/tree
	if(file.is_open())
	{
		file << "    oxoxoo    ooxoo" << std::endl;
		file << "  ooxoxo oo  oxoxooo" << std::endl;
		file << " oooo xxoxoo ooo ooox" << std::endl;
		file << " oxo o oxoxo  xoxxoxo" << std::endl;
		file << "  oxo xooxoooo o ooo" << std::endl;
		file << "    ooo\\oo\\  /o/o" << std::endl;
		file << "        \\  \\/ /" << std::endl;
		file << "         |   /" << std::endl;
		file << "         |  |" << std::endl;
		file << "         | D|" << std::endl;
		file << "         |  |" << std::endl;
		file << "         |  |" << std::endl;
		file << "  ______/____\\____" << std::endl;
		file.close();
	}
}
