/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/14 09:59:08 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cure.hpp"

Cure::Cure()
{
	type = "ice";
	std::cout << type << " default constructor." << std::endl;
}
Cure::Cure(const Cure& src) : AMateria(src)
{
	*this = src;
	std::cout << type << " copy constructor." << std::endl;
}
Cure&	Cure::operator=( Cure const & src )
{
	type = src.type;
	return (*this);
}
Cure::~Cure() { std::cout << type << " destructor." << std::endl; }
void	Cure::use(ICharacter& target)
{
	std::cout << "* heals " << target.getName() << "'s wounds *" << std::endl;
}

Cure	*Cure::clone(void) const
{
	std::cout << "Clone a new " << type << std::endl;
	Cure	*i = new Cure(*this);
	return (i);
}
