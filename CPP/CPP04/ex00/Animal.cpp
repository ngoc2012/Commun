/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/08 14:57:53 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

Animal::Animal() {std::cout << "Animal " << type << " default constructor" << std::endl;}
Animal::Animal(const Animal& src) {
	*this = src;
	std::cout << "Animal " << type << " copy constructor" << std::endl
}
Animal&	Animal::operator=( Animal const & src )
{
	type = src.type;
	return (*this);
}
Animal::~Animal() { std::cout << "Animal " << type << " destructor." << std::endl; }
