/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:17:48 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/21 18:07:57 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Data.hpp"
#include "Serializer.hpp"

int	main()
{
	Data *data = new Data;
	data->login = "minh-ngu";
	data->level = 4.5;
	
	Serializer seri();

	std::cout << "Login: " << seri.deserialize( seri.serialize( data ) )->login << std::endl;
	std::cout << "Level: " << seri.deserialize( seri.serialize( data ) )->level << std::endl;

	delete(data);

	return (0);
}
