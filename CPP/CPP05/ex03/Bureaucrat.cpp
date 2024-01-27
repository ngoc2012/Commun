/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2024/01/27 12:25:56 by ngoc             ###   ########.fr       */
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
	_grade = src.getGrade();
	return (*this);
}

Bureaucrat::Bureaucrat(const std::string __name, int __grade) : _name(__name), _grade(__grade)
{
	std::cout << "Bureaucrat " << _name << " (_grade: " << _grade << ") constructor with parameters." << std::endl;
	if (_grade < MAX_GRADE)
		throw Bureaucrat::GradeTooHighException();
	if (_grade > MIN_GRADE)
		throw Bureaucrat::GradeTooLowException();
}

Bureaucrat::~Bureaucrat()
{
	std::cout << "Bureaucrat " << _name << " destructor." << std::endl;
}

std::string	Bureaucrat::getName( void ) const {return (_name);}
int		Bureaucrat::getGrade( void ) const {return (_grade);}
std::ostream&   operator<<(std::ostream& o, const Bureaucrat& b)
{
	o << b.getName() << ", bureaucrat _grade " << b.getGrade()<< std::endl;
	return (o);
}
void		Bureaucrat::upGrade( void )
{
	if (_grade - 1 < MAX_GRADE)
		throw Bureaucrat::GradeTooHighException();
	_grade--;
	std::cout << "Up _grade succesful : " << *this;
}

void		Bureaucrat::downGrade( void )
{
	if (_grade + 1 > MIN_GRADE)
		throw Bureaucrat::GradeTooLowException();
	_grade++;
	std::cout << "Down _grade succesful : " << *this;
}

const char* Bureaucrat::GradeTooHighException::what() const throw() { return ("Error: Grade is too high."); }

const char* Bureaucrat::GradeTooLowException::what() const throw() { return ("Error: Grade is too low."); }

void		Bureaucrat::signForm( AForm& f )
{
	f.beSigned(*this);
}

void    Bureaucrat::executeForm( const AForm& form ) const {
    try {
        form.execute( *this );
		std::cout << _name << " executed " << form.getName() << std::endl;
    } catch ( std::exception& e ) {
        std::cout << _name << " couldn't execute " << form.getName() << " because " << e.what() << std::endl;
    }
}