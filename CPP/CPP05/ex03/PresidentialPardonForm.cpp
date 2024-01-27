/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2024/01/27 18:43:06 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm(const std::string &t): AForm("PresidentialPardonForm", 25, 5), _target(t) {}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm& src): AForm(src) {}

PresidentialPardonForm&	PresidentialPardonForm::operator=( PresidentialPardonForm const & src )
{
	AForm::operator=(src);
	return (*this);
}

PresidentialPardonForm::~PresidentialPardonForm() {}

void	PresidentialPardonForm::beExecuted() const
{
	std::cout << _target << " has been pardoned by Zaphod Beeblebrox." << std::endl;
}
