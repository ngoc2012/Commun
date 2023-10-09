/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/09 13:00:13 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog() {
	type = "Dog";
	std::cout << type << " default constructor." << std::endl;
}
Dog::Dog(const Dog& src) : Animal(src) {
	*this = src;
	std::cout << type << " copy constructor." << std::endl;
}
Dog&	Dog::operator=( Dog const & src )
{
	type = src.type;
	return (*this);
}
Dog::~Dog() { std::cout << type << " destructor." << std::endl; }
void    Dog::makeSound( void ) const
{
	std::cout << "Gaugau..." << std::endl;
}
