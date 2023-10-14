/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/14 09:58:11 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AMateria.hpp"

AMateria::AMateria() {std::cout << "AMateria " << type << " default constructor." << std::endl;}
AMateria::AMateria(const AMateria& src) {
	*this = src;
	std::cout << "AMateria " << type << " copy constructor." << std::endl;
}
AMateria&	AMateria::operator=( AMateria const & src )
{
	type = src.type;
	return (*this);
}
AMateria::AMateria(std::string const & _type) { type = _type; }
AMateria::~AMateria() { std::cout << "AMateria " << type << " destructor." << std::endl; }
std::string const	&AMateria::getType( void ) const {return (type);}
void    AMateria::use( ICharacter& target ) {(void)target;}
