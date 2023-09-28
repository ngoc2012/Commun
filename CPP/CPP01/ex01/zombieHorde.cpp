/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zombieHorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 18:45:45 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/28 06:26:14 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdio>
#include "Zombie.hpp"

Zombie*	zombieHorde( int N, std::string name )
{	
	char buffer[20];

	Zombie	*list = new Zombie[N];
	for (int i = 0; i < N; i++)
	{
		sprintf(buffer, "%d", i + 1);
		std::string result(buffer);
		list[i].set_name(name + std::string(" ") + result);
	}
	return (list);
}

