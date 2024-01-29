/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:17:48 by ngoc              #+#    #+#             */
/*   Updated: 2024/01/29 13:25:49 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

#include "PmergeMe.hpp"

int	main()
{
	Base*	x;
	Base	b;

	for (int i  = 0; i < 10; i++)
	{
		x = b.generate();
		std::cout << "*x = "; b.identify(x);
		std::cout << ", &a = "; b.identify(*x);
		std::cout << std::endl;
		usleep(1000000);
		delete x;
	}

	return (0);
}
