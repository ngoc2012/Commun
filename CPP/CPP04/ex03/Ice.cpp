/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/13 15:08:45 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ice.hpp"

Ice::Ice()
{
	type = "ice";
	std::cout << type << " default constructor." << std::endl;
}
Ice::Ice(const Ice& src) {
	type = src.type;
	*this = src;
	std::cout << type << " copy constructor." << std::endl;
}
Ice&	Ice::operator=( Ice const & src )
{
	type = src.type;
	return (*this);
}
Ice::~Ice() { std::cout type << " destructor." << std::endl; }
void	Ice::use(ICharacter& target)
{
	std::cout << "* shoots an ice bolt at " << target.type << " *" << std:endl;
}

Ice	*Ice::clone(void) const
{
}
