/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/09 13:25:52 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongCat.hpp"

WrongCat::WrongCat() {
	type = "WrongCat";
	std::cout << type << " default constructor." << std::endl;
}
WrongCat::WrongCat(const WrongCat& src) : WrongAnimal(src) {
	*this = src;
	std::cout << type << " copy constructor." << std::endl;
}
WrongCat&	WrongCat::operator=( WrongCat const & src )
{
	type = src.type;
	return (*this);
}
WrongCat::~WrongCat() { std::cout << type << " destructor." << std::endl; }
void    WrongCat::makeSound( void ) const
{
	std::cout << "MeoGaumeoGau..." << std::endl;
}
