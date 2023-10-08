/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/08 17:25:10 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat() {
	type = "Cat";
	std::cout << type << " default constructor." << std::endl;
}
Cat::Cat(const Cat& src) {
	*this = src;
	std::cout << type << " copy constructor." << std::endl
}
Cat&	Cat::operator=( Cat const & src )
{
	type = src.type;
	return (*this);
}
Cat::~Cat() { std::cout << type << " destructor." << std::endl; }
void    makeSound( void ) const
{
	std::cout << "Meomeo..." << std::endl;
}
