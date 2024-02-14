/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:17:48 by ngoc              #+#    #+#             */
/*   Updated: 2024/02/14 07:35:00 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <list>

#include "easyfind.hpp"

int	main(int argc, char **argv)
{
    std::vector<int>	v;
    std::list<int>	    l;

	for (size_t i = 0; i < 10; i++)
    {
		v.push_back(i + 1);
		l.push_back(i + 1);
    }

	for (int i = 1; i < argc; i++)
    {
        int     n = std::atoi(argv[i]);
        if (easyfind(v, n))
            std::cout << "Found " << n << " in vector" << std::endl;
        else
            std::cout << "Not found " << n << " in vector" << std::endl;
        if (easyfind(l, n))
            std::cout << "Found " << n << " in list" << std::endl;
        else
            std::cout << "Not found " << n << " in list" << std::endl;
    }

	return (0);
}
