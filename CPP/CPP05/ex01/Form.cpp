/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/22 14:05:02 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"

Form&	Form::operator=( Form const & src )
{
	_sign = src.getSign();
	return (*this);
}

Form::Form(const std::string n, int sg, int eg) : _name(n), _sign_grade(sg), _exec_grade(eg)
{
	_sign = false;
	std::cout << "Form " << _name << " (sign grade: " << _sign_grade << ", execute grade: " << _exec_grade << ") constructor with parameters." << std::endl;
}

Form::~Form() { std::cout << "Form " << _name << " destructor." << std::endl; }

std::string	Form::getName( void ) const {return (_name);}
bool		Form::getSign( void ) const {return (_sign);}
int		Form::getSignGrade( void ) const {return (_sign_grade);}
int		Form::getExecGrade( void ) const {return (_exec_grade);}
void		Form::setSign( void ) {_sign = true;}

std::ostream&   operator<<(std::ostream& o, const Form& b)
{
	o << "Form " << b.getName() << ", sign grade " << b.getSignGrade() << ", execute grade " << b.getExecGrade() << std::endl;
	return (o);
}

void		Form::beSigned( Bureaucrat& b)
{
	if (_sign)
	{
		std::cout << "Form " << _name << " already signed." << std::endl;
		return ;
	}
	if (b.getGrade() > sign_grade)
	{
		std::cerr << "Form " << _name << " could not be signed by " << b.getName() << " because: ";
		throw Form::GradeTooLowException();
	}
	_sign = true;
	std::cout << "Form " << _name << " signed by " << b.getName() <<  "." << std::endl;
}
const char* Form::GradeTooHighException::what() const throw() { return ("Grade is too high."); }
const char* Form::GradeTooLowException::what() const throw() { return ("Grade is too low."); }
