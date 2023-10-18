/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:50:42 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/18 07:13:53 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <iostream>

class Bureaucrat
{
	protected:
		std::string	type;
	public:
		Animal();
		Animal(const Animal&);
		Animal &operator=(const Animal& op);
		/*
		Deleting Through Base Class Pointer: The warning occurs when you use the delete operator to destroy an object through a pointer or reference to a base class (e.g., Animal* ptr = new Dog; delete ptr;). If the base class has a non-virtual destructor, it may not correctly call the derived class's destructor, potentially leading to resource leaks or undefined behavior.
		*/
		virtual ~Animal();

		virtual void    makeSound( void ) const;
		std::string     getType( void ) const;
};

std::ostream&   operator<<(std::ostream&, const Bureaucrat&);

#endif
