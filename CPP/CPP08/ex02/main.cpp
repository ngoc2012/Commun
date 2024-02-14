/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:17:48 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/21 19:31:24 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include "Array.hpp"

int	main()
{
	Array<int>	a_int(10);

	for (size_t i = 0; i < 10; i++)
		a_int[i] = i + 1;
	std::cout << a_int << std::endl;

	Array<double>	a_d(10);
	for (size_t i = 0; i < 10; i++)
		a_d[i] = i + 1;
	std::cout << a_d << std::endl;

	try {
		a_int[10] = 5;
	} catch (Array<int>::IndexError& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (0);
}
