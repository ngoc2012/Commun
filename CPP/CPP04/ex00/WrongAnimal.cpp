/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/14 16:47:45 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal() {std::cout << "WrongAnimal " << type << " default constructor." << std::endl;}
WrongAnimal::WrongAnimal(const WrongAnimal& src) {
	*this = src;
	std::cout << "WrongAnimal " << type << " copy constructor." << std::endl;
}
WrongAnimal&	WrongAnimal::operator=( WrongAnimal const & src )
{
	type = src.type;
	return (*this);
}
WrongAnimal::~WrongAnimal() { std::cout << "WrongAnimal " << type << " destructor." << std::endl; }
void    WrongAnimal::makeSound( void ) const
{
	std::cout << "hoohooohohohohoho..." << std::endl;
}
std::string     WrongAnimal::getType( void ) const {return (type);}
