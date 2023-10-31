/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/31 08:50:22 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm(std::string t)
{
	sign = false;
	target = t;
	sign_grade = 25;
	exec_grade = 5;
	std::cout << "PresidentialPardonForm " << name << " default constructor." << std::endl;
}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm& src): AForm(src)
{
	std::cout << "PresidentialPardonForm " << name << " copy constructor." << std::endl;
}

PresidentialPardonForm&	PresidentialPardonForm::operator=( PresidentialPardonForm const & src )
{
	AForm::operator=(src);
	return (*this);
}

PresidentialPardonForm::~PresidentialPardonForm() { std::cout << "PresidentialPardonForm " << name << " destructor." << std::endl; }

void	PresidentialPardonForm::beExecuted() const
{
	std::cout << target << " has been pardoned by Zaphod Beeblebrox." << std::endl;
}
