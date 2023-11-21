/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:17:48 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/21 18:06:40 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
uintptr_t: Hold a pointer converted to an integer without loss of information

reinterpret_cast is a type of C++ casting operator that is used for converting one pointer type to another, or one integral type to another. It is the most powerful and potentially dangerous of the C++ casting operators because it can perform conversions that are not type-safe.

No checks: Unlike dynamic_cast or static_cast, reinterpret_cast does not perform any runtime checks to ensure the validity of the conversion. It simply tells the compiler to treat the pointer or value as if it were of the new type.

*/

Serializer::Serializer() {}

Serializer::Serializer(const Serializer& src) { *this = src; }

Serializer&	Serializer::operator=( Serializer const & src )
{
	(void) src;
	return (*this);
}

Serializer::~Serializer() {}

uintptr_t	Serializer::serialize( Data *data ) {
	return ( reinterpret_cast< uintptr_t >( data ) );
}

Data*		Serializer::deserialize( uintptr_t data ) {
	return ( reinterpret_cast< Data* >( data ) );
}
