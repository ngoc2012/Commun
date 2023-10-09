/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:50:42 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/09 13:24:41 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRONGANIMAL_HPP
# define WRONGANIMAL_HPP

#include <iostream>

class WrongAnimal
{
	protected:
		std::string	type;
	public:
		WrongAnimal();
		WrongAnimal(const WrongAnimal&);
		WrongAnimal &operator=(const WrongAnimal& op);
		/*
		Deleting Through Base Class Pointer: The warning occurs when you use the delete operator to destroy an object through a pointer or reference to a base class (e.g., WrongAnimal* ptr = new Dog; delete ptr;). If the base class has a non-virtual destructor, it may not correctly call the derived class's destructor, potentially leading to resource leaks or undefined behavior.
		*/
		virtual ~WrongAnimal();

		virtual void    makeSound( void ) const;
		std::string     getType( void ) const;
};

#endif
