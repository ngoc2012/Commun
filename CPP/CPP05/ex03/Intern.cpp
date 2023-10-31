/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/31 09:06:38 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"

Intern::Intern() {std::cout << "Intern " << name << " default constructor." << std::endl;}

Intern::Intern(const Intern& src) {
	*this = src;
	std::cout << "Intern " << name << " copy constructor." << std::endl;
}

Intern&	Intern::operator=( Intern const & src )
{
	return (*this);
}

Intern::Intern(const std::string n, int sg, int eg) : name(n), sign_grade(sg), exec_grade(eg)
{
	sign = false;
	std::cout << "Intern " << name << " (sign grade: " << sign_grade << ", execute grade: " << exec_grade << ") constructor with parameters." << std::endl;
}

Intern::~Intern() { std::cout << "Intern " << name << " destructor." << std::endl; }

std::string	Intern::getName( void ) const {return (name);}
bool		Intern::getSign( void ) const {return (sign);}
int		Intern::getSignGrade( void ) const {return (sign_grade);}
int		Intern::getExecGrade( void ) const {return (exec_grade);}
void		Intern::setSign( void ) {sign = true;}

std::ostream&   operator<<(std::ostream& o, const Intern& b)
{
	o << "Intern " << b.getName() << ", sign grade " << b.getSignGrade() << ", execute grade " << b.getExecGrade() << std::endl;
	return (o);
}

void		Intern::beSigned( Bureaucrat& b)
{
	if (sign)
	{
		std::cout << "Intern " << name << " already signed." << std::endl;
		return ;
	}
	if (b.getGrade() > sign_grade)
	{
		std::cerr << "Intern " << name << " could not be signed by " << b.getName() << " because: ";
		throw Intern::GradeTooLowException();
	}
	sign = true;
	std::cout << "Intern " << name << " signed by " << b.getName() <<  "." << std::endl;
}
const char* Intern::GradeTooHighException::what() const throw() { return ("Grade is too high."); }
const char* Intern::GradeTooLowException::what() const throw() { return ("Grade is too low."); }
const char* Intern::FormNotSigned::what() const throw() { return ("Form not signed."); }
void		Intern::execute(Bureaucrat const & executor) const
{
	if (!sign)
		throw Intern:: FormNotSigned();
	else if (executor.getGrade() > exec_grade)
		throw Intern::GradeTooLowException();
	beExecuted();
}
