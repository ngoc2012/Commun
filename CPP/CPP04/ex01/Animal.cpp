/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/10 15:01:19 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

Animal::Animal() {std::cout << "Animal " << type << " default constructor." << std::endl;}
Animal::Animal(const Animal& src) {
	*this = src;
	std::cout << "Animal " << type << " copy constructor." << std::endl;
}
Animal&	Animal::operator=( Animal const & src )
{
	type = src.type;
	return (*this);
}
Animal::~Animal() { std::cout << "Animal " << type << " destructor." << std::endl; }
void    Animal::makeSound( void ) const
{
	std::cout << "Animal make sound." << std::endl;
}
std::string     Animal::getType( void ) const {return (type);}
void    Animal::showBrain( void ) const {}
void	Animal::setBrain(std::string s, int i)
{
	(void)s;
	(void)i;
}
