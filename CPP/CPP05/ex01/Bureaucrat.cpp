/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/22 14:06:08 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat()
{
	std::cout << "Bureaucrat " << _name << " default constructor." << std::endl;
}

Bureaucrat::Bureaucrat(const Bureaucrat& src) {
	*this = src;
	std::cout << "Bureaucrat " << _name << " copy constructor." << std::endl;
}

Bureaucrat&	Bureaucrat::operator=( Bureaucrat const & src )
{
	_name = src.name;
	_grade = src.grade;
	return (*this);
}

Bureaucrat::Bureaucrat(const std::string name, int grade) : _name(name), _grade(grade)
{
	std::cout << "Bureaucrat " << _name << " (grade: " << _grade << ") constructor with parameters." << std::endl;
	if (_grade < MAX_GRADE)
		throw Bureaucrat::GradeTooHighException();
	if (_grade > MIN_GRADE)
		throw Bureaucrat::GradeTooLowException();
}

Bureaucrat::~Bureaucrat()
{
	std::cout << "Bureaucrat " << name << " destructor." << std::endl;
}

std::string	Bureaucrat::getName( void ) const {return (name);}
int		Bureaucrat::getGrade( void ) const {return (grade);}
std::ostream&   operator<<(std::ostream& o, const Bureaucrat& b)
{
	o << b.getName() << ", bureaucrat grade " << b.getGrade()<< std::endl;
	return (o);
}
void		Bureaucrat::upGrade( void )
{
	if (grade - 1 < MAX_GRADE)
		throw Bureaucrat::GradeTooHighException();
	grade--;
	std::cout << "Up grade succesful : " << *this;
}

void		Bureaucrat::downGrade( void )
{
	if (grade + 1 > MIN_GRADE)
		throw Bureaucrat::GradeTooLowException();
	grade++;
	std::cout << "Down grade succesful : " << *this;
}

const char* Bureaucrat::GradeTooHighException::what() const throw() { return ("Error: Grade is too high."); }

const char* Bureaucrat::GradeTooLowException::what() const throw() { return ("Error: Grade is too low."); }

void		Bureaucrat::signForm( Form& f )
{
	f.beSigned(*this);
}
