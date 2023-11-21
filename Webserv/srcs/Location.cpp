/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/21 08:58:45 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Location.hpp"
#include "Host.hpp"

Location::Location()
{
}
Location::Location(const Location& src) { *this = src; }
Location&	Location::operator=( Location const & src )
{
	(void) src;
	return (*this);
}
Location::~Location() {}

std::vector<e_method>		Location::get_methods(void) const {return (_methods);}
std::string			Location::get_alias(void) const {return (_alias);}

void				Location::insert_methods(e_method e) {_methods.push_back(e);}
void				Location::set_alias(std::string s) {_alias = s;}
