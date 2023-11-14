/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:17:48 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/14 14:53:17 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

struct Data
{
	std::string	name;
	float	level;
};

uintptr_t    serialize( Data *data ) {
	return ( reinterpret_cast< uintptr_t >( data ) );
}

Data*   deserialize( uintptr_t data ) {
	return ( reinterpret_cast< Data* >( data ) );
}

int main( void )
{
	Data *data = new Data;

	data->name = "achraf";
	data->age = 30;

	std::cout << "Name: " << deserialize( serialize( data ) )->name << std::endl;
	std::cout << "Age: " << deserialize( serialize( data ) )->age << std::endl;

	delete data;

	return EXIT_SUCCESS;
}
