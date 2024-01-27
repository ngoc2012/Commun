/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2024/01/27 12:27:24 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm(const std::string &t)
{
	_sign = false;
	_target = t;
	_sign_grade = 25;
	_exec_grade = 5;
	std::cout << "PresidentialPardonForm " << _name << " default constructor." << std::endl;
}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm& src): AForm(src)
{
	std::cout << "PresidentialPardonForm " << _name << " copy constructor." << std::endl;
}

PresidentialPardonForm&	PresidentialPardonForm::operator=( PresidentialPardonForm const & src )
{
	AForm::operator=(src);
	return (*this);
}

PresidentialPardonForm::~PresidentialPardonForm() { std::cout << "PresidentialPardonForm " << _name << " destructor." << std::endl; }

void	PresidentialPardonForm::beExecuted() const
{
	std::cout << _target << " has been pardoned by Zaphod Beeblebrox." << std::endl;
}
