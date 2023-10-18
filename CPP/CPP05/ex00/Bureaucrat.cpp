/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/18 07:34:44 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat() {std::cout << "Bureaucrat " << name << " default constructor." << std::endl;}
Bureaucrat::Bureaucrat(const Bureaucrat& src) {
	*this = src;
	std::cout << "Bureaucrat " << name << " copy constructor." << std::endl;
}
Bureaucrat&	Bureaucrat::operator=( Bureaucrat const & src )
{
	name = src.name;
	grade = src.grade;
	return (*this);
}
Bureaucrat::~Bureaucrat() { std::cout << "Bureaucrat " << name << " destructor." << std::endl; }
void    Bureaucrat::makeSound( void ) const
{
	std::cout << "Bureaucrat make sound." << std::endl;
}
std::string	Bureaucrat::getName( void ) const {return (name);}
int		Bureaucrat::getGrade( void ) const {return (grade);}

std::ostream&   operator<<(std::ostream& o, const Bureaucrat& b);
{
	o << b.getName() << ", bureaucrat grade " << b.getGrade()<< std::endl;
}

const char* Bureaucrat::GradeTooHighException::what() const throw() { return ("Grade is too high."); }
const char* Bureaucrat::GradeTooLowException::what() const throw() { return ("Grade is too low."); }
