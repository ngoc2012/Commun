/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/18 18:44:17 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"

Form::Form() {std::cout << "Form " << name << " default constructor." << std::endl;}
Form::Form(const Form& src) {
	*this = src;
	std::cout << "Form " << name << " copy constructor." << std::endl;
}
Form&	Form::operator=( Form const & src )
{
	name = src.name;
	grade = src.grade;
	return (*this);
}
Bureaucrat::Bureaucrat(const std::string n, int sg, int eg) : name(n), sign_grade(sg), exec_grade(eg)
{
	std::cout << "Form " << name << " (grade: " << grade << ") constructor with parameters." << std::endl;
	if (grade < MAX_GRADE)
		throw Form::GradeTooHighException();
	if (grade > MIN_GRADE)
		throw Form::GradeTooLowException();
}
Form::~Form() { std::cout << "Form " << name << " destructor." << std::endl; }
std::string	Form::getName( void ) const {return (name);}
bool		Form::getSign( void ) const {return (sign);}
int		Form::getSignGrade( void ) const {return (sign_grade);}
int		Form::getExecGrade( void ) const {return (exec_grade);}
std::ostream&   operator<<(std::ostream& o, const Form& b)
{
	o << b.getName() << ", bureaucrat grade " << b.getGrade()<< std::endl;
	return (o);
}
void		Form::beSigned( Bureaucrat& b);
{
	if (grade - 1 < MAX_GRADE)
		throw Form::GradeTooHighException();
	grade--;
	std::cout << "Up grade succesful : " << *this;
}
void		Form::downGrade( void )
{
	if (grade + 1 > MIN_GRADE)
		throw Form::GradeTooLowException();
	grade++;
	std::cout << "Down grade succesful : " << *this;
}
const char* Form::GradeTooHighException::what() const throw() { return ("Error: Grade is too high."); }
const char* Form::GradeTooLowException::what() const throw() { return ("Error: Grade is too low."); }
