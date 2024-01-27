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

PresidentialPardonForm::PresidentialPardonForm(const std::string &t): AForm("PresidentialPardonForm", 25, 5), _target(t) {}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm& src): AForm(src)
{
	_target = src.
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
