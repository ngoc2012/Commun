/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cube.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/13 17:56:48 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.hpp"

Cub::Cub()
{
	type = "ice";
	std::cout << type << " default constructor." << std::endl;
}
Cub::Cub(const Cub& src) {
	*this = src;
	std::cout << type << " copy constructor." << std::endl;
}
Cub&	Cub::operator=( Cub const & src )
{
	type = src.type;
	return (*this);
}
Cub::~Cub() { std::cout type << " destructor." << std::endl; }
void	Cub::use(ICharacter& target)
{
	std::cout << "* heals " << target.getName() << "'s wounds *" << std:endl;
}

Cub	*Cub::clone(void) const
{
	return (Cub(*this));
}
