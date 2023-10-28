/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/28 13:55:42 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm() {std::cout << "ShrubberyCreationForm " << name << " default constructor." << std::endl;}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& src) {
	*this = src;
	std::cout << "ShrubberyCreationForm " << name << " copy constructor." << std::endl;
}

ShrubberyCreationForm&	ShrubberyCreationForm::operator=( ShrubberyCreationForm const & src )
{
	name = src.name;
	sign = src.sign;
	sign_grade = src.sign_grade;
	exec_grade = src.exec_grade;
	return (*this);
}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string n, int sg, int eg) : name(n), sign_grade(sg), exec_grade(eg)
{
	sign = false;
	std::cout << "ShrubberyCreationForm " << name << " (sign grade: " << sign_grade << ", execute grade: " << exec_grade << ") constructor with parameters." << std::endl;
}

ShrubberyCreationForm::~ShrubberyCreationForm() { std::cout << "ShrubberyCreationForm " << name << " destructor." << std::endl; }
