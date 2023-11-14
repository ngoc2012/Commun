/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:17:48 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/14 14:54:46 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

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

	std::cout << "Login: " << deserialize( serialize( data ) )->name << std::endl;
	std::cout << "Level: " << deserialize( serialize( data ) )->age << std::endl;

	delete data;

	return EXIT_SUCCESS;
}
