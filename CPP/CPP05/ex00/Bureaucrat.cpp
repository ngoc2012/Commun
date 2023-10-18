/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/18 07:15:59 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat() {std::cout << "Bureaucrat " << type << " default constructor." << std::endl;}
Bureaucrat::Bureaucrat(const Bureaucrat& src) {
	*this = src;
	std::cout << "Bureaucrat " << type << " copy constructor." << std::endl;
}
Bureaucrat&	Bureaucrat::operator=( Bureaucrat const & src )
{
	type = src.type;
	return (*this);
}
Bureaucrat::~Bureaucrat() { std::cout << "Bureaucrat " << type << " destructor." << std::endl; }
void    Bureaucrat::makeSound( void ) const
{
	std::cout << "Bureaucrat make sound." << std::endl;
}
std::string	Bureaucrat::getName( void ) const {return (name);}
int		Bureaucrat::getGrade( void ) const {return (grade);}

std::ostream&   operator<<(std::ostream& o, const Bureaucrat& b);
{
	o << b.getName() << std::endl;
}
