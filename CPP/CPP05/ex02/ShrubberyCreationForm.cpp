/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2024/01/27 18:38:17 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"

//ShrubberyCreationForm::ShrubberyCreationForm(std::string t) : target(t)
ShrubberyCreationForm::ShrubberyCreationForm(const std::string t): AForm("RobotomyRequestForm", 72, 45), _target(t) {}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& src): AForm(src) { }

ShrubberyCreationForm&	ShrubberyCreationForm::operator=( ShrubberyCreationForm const & src )
{
	AForm::operator=(src);
	return (*this);
}

ShrubberyCreationForm::~ShrubberyCreationForm() { }

void	ShrubberyCreationForm::beExecuted() const
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
