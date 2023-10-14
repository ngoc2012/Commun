/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/14 09:58:48 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ice.hpp"

Ice::Ice()
{
	type = "ice";
	std::cout << type << " default constructor." << std::endl;
}
Ice::Ice(const Ice& src) : AMateria(src)
{
	*this = src;
	std::cout << type << " copy constructor." << std::endl;
}
Ice&	Ice::operator=( Ice const & src )
{
	type = src.type;
	return (*this);
}
Ice::~Ice() { std::cout << type << " destructor." << std::endl; }
void	Ice::use(ICharacter& target)
{
	std::cout << "* shoots an ice bolt at " << target.getName() << " *" << std::endl;
}

Ice	*Ice::clone(void) const
{
	std::cout << "Clone a new " << type << std::endl;
	Ice	*i = new Ice(*this);
	return (i);
}
