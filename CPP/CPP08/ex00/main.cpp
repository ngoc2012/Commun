/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:17:48 by ngoc              #+#    #+#             */
/*   Updated: 2024/02/14 07:31:46 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <list>

#include "Array.hpp"

int	main(int argc, char **argv)
{
    std::vector<int>	v;

	for (size_t i = 0; i < 10; i++)
		v.push_back(i + 1);

	for (size_t i = 1; i < argc; i++)
    {
        int     n = std::atoi(argv[i]);
        if (easyfind(v, n))
            std::cout << "Found " << n << " in vector" << std::endl;
        else
            std::cout << "Not found " << n << " in vector" << std::endl;
    }

	return (0);
}
