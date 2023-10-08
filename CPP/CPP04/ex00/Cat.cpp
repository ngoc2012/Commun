/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/08 15:40:01 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat() {std::cout << "Cat " << type << " default constructor." << std::endl;}
Cat::Cat(const Cat& src) {
	*this = src;
	std::cout << "Cat " << type << " copy constructor." << std::endl
}
Cat&	Cat::operator=( Cat const & src )
{
	type = src.type;
	return (*this);
}
Cat::~Cat() { std::cout << "Cat " << type << " destructor." << std::endl; }
void    makeSound( void ) const
{
	std::cout << "Cat make sound." << std::endl;
}
std::string     getType( void ) const {return (type);}
