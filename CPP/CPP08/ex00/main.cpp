/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:17:48 by ngoc              #+#    #+#             */
/*   Updated: 2024/02/14 07:27:11 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <list>

#include "Array.hpp"

int	main(int argc, char **argv)
{
    std::vector<int>	a_int(10);

	for (size_t i = 0; i < 10; i++)
		a_int[i] = i + 1;
	for (size_t i = 1; i < argc; i++)
    {
        if (easyfind(a_int, 5))
            std::cout << "Found" << std::endl;
        else
            std::cout << "Not found" << std::endl;
    }

	return (0);
}
