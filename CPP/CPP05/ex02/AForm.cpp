/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2024/01/27 12:22:26 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"

AForm::AForm(const AForm& src): _name(src.getName()), _sign_grade(src.getSignGrade()), _exec_grade(src.getExecGrade())
{
	std::cout << "AForm " << _name << " copy constructor." << std::endl;
}

AForm&	AForm::operator=( AForm const & src )
{
	_sign = src.getSign();
	return (*this);
}

AForm::AForm(const std::string n, int sg, int eg) : _name(n), _sign_grade(sg), _exec_grade(eg)
{
	_sign = false;
	std::cout << "AForm " << _name << " (sign grade: " << _sign_grade << ", execute grade: " << exec_grade << ") constructor with parameters." << std::endl;
}

AForm::~AForm() { std::cout << "AForm " << _name << " destructor." << std::endl; }

std::string	AForm::getName( void ) const {return (_name);}
bool		AForm::getSign( void ) const {return (sign);}
int		AForm::getSignGrade( void ) const {return (sign_grade);}
int		AForm::getExecGrade( void ) const {return (exec_grade);}
void		AForm::setSign( void ) {sign = true;}

std::ostream&   operator<<(std::ostream& o, const AForm& b)
{
	o << "AForm " << b.getName() << ", sign grade " << b.getSignGrade() << ", execute grade " << b.getExecGrade() << std::endl;
	return (o);
}

void		AForm::beSigned( Bureaucrat& b)
{
	if (sign)
	{
		std::cout << "AForm " << _name << " already signed." << std::endl;
		return ;
	}
	if (b.getGrade() > sign_grade)
	{
		std::cerr << "AForm " << _name << " could not be signed by " << b.getName() << " because: ";
		throw AForm::GradeTooLowException();
	}
	sign = true;
	std::cout << "AForm " << _name << " signed by " << b.getName() <<  "." << std::endl;
}
const char* AForm::GradeTooHighException::what() const throw() { return ("Grade is too high."); }
const char* AForm::GradeTooLowException::what() const throw() { return ("Grade is too low."); }
const char* AForm::FormNotSigned::what() const throw() { return ("Form not signed."); }
void		AForm::execute(Bureaucrat const & executor) const
{
	if (!sign)
		throw AForm:: FormNotSigned();
	else if (executor.getGrade() > exec_grade)
		throw AForm::GradeTooLowException();
	beExecuted();
}
