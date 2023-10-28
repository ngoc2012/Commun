/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/28 18:09:21 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"

//ShrubberyCreationForm::ShrubberyCreationForm(std::string t) : target(t)
ShrubberyCreationForm::ShrubberyCreationForm(std::string t)
{
	sign = false;
	target = t;
	sign_grade = 145;
	exec_grade = 137;
	std::cout << "ShrubberyCreationForm " << name << " default constructor." << std::endl;
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& src): AForm(src)
{
	std::cout << "ShrubberyCreationForm " << name << " copy constructor." << std::endl;
}

ShrubberyCreationForm&	ShrubberyCreationForm::operator=( ShrubberyCreationForm const & src )
{
	AForm::operator=(src);
	return (*this);
}

ShrubberyCreationForm::~ShrubberyCreationForm() { std::cout << "ShrubberyCreationForm " << name << " destructor." << std::endl; }

void	ShrubberyCreationForm::beExecuted() const
{
	std::ofstream file;

	file.open(std::string(target + "_shrubbery").c_str(),
		std::ios::out | std::ios::app);
	// https://ascii.co.uk/art/tree
	if(file.is_open())
	{
file << "    oxoxoo    ooxoo
file << "  ooxoxo oo  oxoxooo
file << " oooo xxoxoo ooo ooox
file << " oxo o oxoxo  xoxxoxo
file << "  oxo xooxoooo o ooo
file << "    ooo\\oo\\  /o/o
file << "        \\  \\/ /
file << "         |   /
file << "         |  |
file << "         | D|
file << "         |  |
file << "         |  |
file << "  ______/____\\____

		file << "                 # #### ####			" << std::endl;
		file << "               ### \\/#|### |/####		" << std::endl;
		file << "              ##\\/#/ \\||/##/_/##/_#	" << std::endl;
		file << "            ###  \\/###|/ \\/ # ###	" << std::endl;
		file << "          ##_\\_#\\_\\## | #/###_/_####" << std::endl;
		file << "         ## #### # \\ #| /  #### ##/##	" << std::endl;
		file << "          __#_--###`  |{,###---###-~	" << std::endl;
		file << "                    \\ }{				" << std::endl;
		file << "                     }}{				" << std::endl;
		file << "                     }}{				" << std::endl;
		file << "                     {{}				" << std::endl;
		file << "                     {}}				" << std::endl;
		file << "                    {}{{}}				" << std::endl;
		file.close();
	}
}
