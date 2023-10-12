/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/12 09:52:00 by minh-ngu         ###   ########.fr       */
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
