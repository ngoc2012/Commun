/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/10 14:29:32 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog() {
	brain = new Brain();
	type = "Dog";
	std::cout << type << " default constructor." << std::endl;
}
Dog::Dog(const Dog& src) : Animal(src) {
	brain = new Brain();
	*this = src;
	std::cout << type << " copy constructor." << std::endl;
}
Dog&	Dog::operator=( Dog const & src )
{
	brain = src.brain;
	type = src.type;
	return (*this);
}
Dog::~Dog()
{
	delete(brain);
	std::cout << type << " destructor." << std::endl;
}
void    Dog::makeSound( void ) const
{
	std::cout << "Gaugau..." << std::endl;
}
