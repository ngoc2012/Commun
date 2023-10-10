/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:50:42 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/10 13:06:55 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMAL_HPP
# define ANIMAL_HPP

#include <iostream>
#include "Brain.hpp"

class Animal
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

#endif
