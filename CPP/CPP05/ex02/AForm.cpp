/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/28 14:47:55 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"

AForm::AForm() {std::cout << "AForm " << name << " default constructor." << std::endl;}

AForm::AForm(const AForm& src) {
	*this = src;
	std::cout << "AForm " << name << " copy constructor." << std::endl;
}

AForm&	AForm::operator=( AForm const & src )
{
	name = src.name;
	sign = src.sign;
	sign_grade = src.sign_grade;
	exec_grade = src.exec_grade;
	return (*this);
}

AForm::AForm(const std::string n, int sg, int eg) : name(n), sign_grade(sg), exec_grade(eg)
{
	sign = false;
	std::cout << "AForm " << name << " (sign grade: " << sign_grade << ", execute grade: " << exec_grade << ") constructor with parameters." << std::endl;
}

AForm::~AForm() { std::cout << "AForm " << name << " destructor." << std::endl; }

std::string	AForm::getName( void ) const {return (name);}
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
		std::cout << "AForm " << name << " already signed." << std::endl;
		return ;
	}
	if (b.getGrade() > sign_grade)
	{
		std::cerr << "AForm " << name << " could not be signed by " << b.getName() << " because: ";
		throw AForm::GradeTooLowException();
	}
	sign = true;
	std::cout << "AForm " << name << " signed by " << b.getName() <<  "." << std::endl;
}
const char* AForm::GradeTooHighException::what() const throw() { return ("Grade is too high."); }
const char* AForm::GradeTooLowException::what() const throw() { return ("Grade is too low."); }
void		execute(Bureaucrat const & executor) const
{
	if (!sign)
		throw std::string("Form not signed.");
	else if (executor.getGrade() > exec_grade)
		throw AForm::GradeTooLowException();
	this->beExecuted();
}
