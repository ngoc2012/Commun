/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/18 19:11:53 by ngoc             ###   ########.fr       */
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
	sign = src.sign;
	sign_grade = src.sign_grade;
	exec_grade = src.exec_grade;
	return (*this);
}
Form::Form(const std::string n, int sg, int eg) : name(n), sign_grade(sg), exec_grade(eg)
{
	std::cout << "Form " << name << " (sign grade: " << sign_grade << ", execute grade: " << exec_grade << ") constructor with parameters." << std::endl;
}
Form::~Form() { std::cout << "Form " << name << " destructor." << std::endl; }
std::string	Form::getName( void ) const {return (name);}
bool		Form::getSign( void ) const {return (sign);}
int		Form::getSignGrade( void ) const {return (sign_grade);}
int		Form::getExecGrade( void ) const {return (exec_grade);}
std::ostream&   operator<<(std::ostream& o, const Form& b)
{
	o << "Form " << b.getName() << ", sign grade " << b.getSignGrade() << ", execute grade " << b.getExecGrade() << std::endl;
	return (o);
}
void		Form::beSigned( Bureaucrat& b)
{
	if (b.getGrade() > sign_grade)
		throw Form::GradeTooLowException();
	std::cout << "Form " << name << " signed.";
}
const char* Form::GradeTooHighException::what() const throw() { return ("Error: Grade is too high."); }
const char* Form::GradeTooLowException::what() const throw() { return ("Error: Grade is too low."); }
