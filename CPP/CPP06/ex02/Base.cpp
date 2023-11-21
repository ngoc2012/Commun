/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:17:48 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/21 18:38:52 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"


Base::Base() {}

Base::Base(const Base& src) { *this = src; }

Base&	Base::operator=( Base const & src )
{
	(void) src;
	return (*this);
}

Base::~Base() {}

uintptr_t	Base::serialize( Data *data ) {
	return ( reinterpret_cast< uintptr_t >( data ) );
}

Data*		Base::deserialize( uintptr_t data ) {
	return ( reinterpret_cast< Data* >( data ) );
}
