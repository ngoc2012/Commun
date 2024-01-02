/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Listing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2024/01/02 16:41:45 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"
#include "Response.hpp"
#include "webserv.hpp"

#include "Listing.hpp"

Listing::Listing()
{
	std::cout << "Listing Default constructor" << std::endl;
}
Listing::Listing(const Listing& src) { *this = src; }
Listing&	Listing::operator=( Listing const & src )
{
	(void) src;
	return (*this);
}
Listing::~Listing() {}

std::string Listing::get_html(Response* response)
{
    (void)response;
    return "Listing";
}
