/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:17:48 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/14 15:06:19 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
//#include <cstdint>
#include <stdint.h>

/*
uintptr_t: Hold a pointer converted to an integer without loss of information

reinterpret_cast is a type of C++ casting operator that is used for converting one pointer type to another, or one integral type to another. It is the most powerful and potentially dangerous of the C++ casting operators because it can perform conversions that are not type-safe.

No checks: Unlike dynamic_cast or static_cast, reinterpret_cast does not perform any runtime checks to ensure the validity of the conversion. It simply tells the compiler to treat the pointer or value as if it were of the new type.

*/

struct Data
{
	std::string	login;
	float		level;
};

uintptr_t	serialize( Data *data ) {
	return ( reinterpret_cast< uintptr_t >( data ) );
}

Data*	deserialize( uintptr_t data ) {
	return ( reinterpret_cast< Data* >( data ) );
}

int	main()
{
	Data *data = new Data;

	data->login = "minh-ngu";
	data->level = 4.5;

	std::cout << "Login: " << deserialize( serialize( data ) )->login << std::endl;
	std::cout << "Level: " << deserialize( serialize( data ) )->level << std::endl;

	delete(data);

	return (0);
}
